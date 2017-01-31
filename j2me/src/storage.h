/***************************************************************************************\

                                     Storage unit

                                     version 0.04

                          ***********************************

   Export:

      TBuffer  loadDataBlock(int index)

      bool  saveDataBlock(TBuffer data, int index)

      bool  deleteDataBlock(int index)

      bool  isDataBlockExist(int index)

\***************************************************************************************/



static final TBuffer loadDataBlock(int index) {
   return res_readRecord(index);
}


static final bool saveDataBlock(TBuffer data, int index) {
   return res_writeRecord(index, data);
}



static final bool deleteDataBlock(int index) {
   return res_removeRecord(index);
}



static final bool isDataBlockExist(int index) {
   return res_isResourceExist(index);
}



//--------------------------------------------------------------------------------------//
//                        internal variables and functions                              //
//--------------------------------------------------------------------------------------//
// число элементов, сохраненных в RMS
static int res_objectsCount;

// индексы элементов, хранимых в RMS. находятся в отсортированном состоянии.
// массивы может быть очищен в случае нехватки памяти, поэтому, при обращении надо проверять
// факт агрузки
static int[] res_objectsIndexes;

// id элементов в RMS. также могут быть очищены.
// в случае удаления элемента, его индекс получит значение -1, что значит, что в эту ячейку
// можно будет добавить следующий элемент
static int[] res_objectsOffsets;

// имя хранилища RMS
static final TString RES_STORAGE_NAME = "data";



// читает заголовок блока RMS
static final bool res_readHeader() {
   bool result = true;
   RecordStore rs = null;
   try {
     rs = RecordStore.openRecordStore(RES_STORAGE_NAME, false);
     byte buf[] = rs.getRecord(1);
     if ( buf != null ) {
        try {
           DataInputStream is = new DataInputStream(new ByteArrayInputStream(buf));
           int cnt = is.readInt();
           res_objectsCount = cnt;
           if ( res_objectsIndexes == null || res_objectsIndexes.length != cnt )
             res_objectsIndexes = new int[cnt];
           if ( res_objectsOffsets == null || res_objectsOffsets.length != cnt )
             res_objectsOffsets = new int[cnt];
           for (int i = 0; i < cnt; i++)
             res_objectsIndexes[i] = is.readInt();
           for (int i = 0; i < cnt; i++)
             res_objectsOffsets[i] = is.readInt();
           is.close();
        } catch ( IOException ioe ) { result = false; }

     } else
       result = false;
   } catch ( RecordStoreException rse ) { result = false; }
   if ( rs != null )
     try {
        rs.closeRecordStore();
     } catch ( RecordStoreException rse ) { result = false; }
   return result;
}



// записывает заголовок блока из памяти в RMS
static final bool res_writeHeader() {
   bool result = true;
   RecordStore rs = null;
   try {
      rs = RecordStore.openRecordStore(RES_STORAGE_NAME, true);
      byte[] buf = null;
      try {
         ByteArrayOutputStream bos = new ByteArrayOutputStream();
         DataOutputStream os = new DataOutputStream(bos);
         os.writeInt(res_objectsCount);
         for (int i = 0; i < res_objectsCount; i++)
            os.writeInt(res_objectsIndexes[i]);
         for (int i = 0; i < res_objectsCount; i++)
            os.writeInt(res_objectsOffsets[i]);
         buf = bos.toByteArray();
         os.close();
      } catch ( IOException ioe ) { result = false; }

      if ( rs.getNumRecords() == 0 )
         rs.addRecord(buf, 0, buf.length);
      else
         rs.setRecord(1, buf, 0, buf.length);
   } catch ( RecordStoreException rse ) { result = false; }
   if ( rs != null )
      try {
         rs.closeRecordStore();
      } catch ( RecordStoreException rse ) { result = false; }
   return result;
}




// в отсортированном массиве блока RMS помещает 1й неотсортированый элемент itemIndex на свое место
// возвращает позицию, в которую был помещен этот элемент
static final int res_sortHeaderItem() {
   if ( res_objectsCount <= 1 )
      return 0;
   int newIndex = 1;
   int valI = res_objectsIndexes[0];
   int valO = res_objectsOffsets[0];
   while ( newIndex < res_objectsCount && res_objectsIndexes[newIndex] < valI )
      newIndex++;
   newIndex--;
   for (int i = 0; i < newIndex; i++) {
      res_objectsIndexes[i] = res_objectsIndexes[i+1];
      res_objectsOffsets[i] = res_objectsOffsets[i+1];
   }
   res_objectsIndexes[newIndex] = valI;
   res_objectsOffsets[newIndex] = valO;
   return newIndex;
}



// читает запись из блока RMS по ее индексу
static final TBuffer res_readRecord(int index) {
   // ищем запись и определяем ее id
   if ( res_objectsIndexes == null )
      if ( !res_readHeader() )
         return null;
   int ind = binarySearchInt(res_objectsIndexes, res_objectsCount, index);
   if ( ind < 0 )
      return null;
   int recId = res_objectsOffsets[ind];

   byte[] result = null;
   RecordStore rs = null;
   try {
     rs = RecordStore.openRecordStore(RES_STORAGE_NAME, false);
     result = rs.getRecord(recId);
   } catch ( RecordStoreException rse ) { result = null; }
   if ( rs != null )
     try {
        rs.closeRecordStore();
     } catch ( RecordStoreException rse ) { result = null; }
   return result;
}



// сохраняет запись в блоке RMS. если такая запись уже существует, обновляет ее, иначе добавляет новую
static final bool res_writeRecord(int index, TBuffer rec) {
   // ищем, не существует ли такой записи
   int headerIndex;          // индекс ячейки в заголовке
   bool append;              // если установлен, то запись будет добавлена в RMS, иначе - изменение
   bool firstWrite = false;  // это первая операция записи в блок
   // пытаемся считать заголовок, если он еще не загружен
   if ( res_objectsIndexes == null )
      res_readHeader();
   // если прочитать его не удалось, считаем, что это первое обращене к RMS и создаем заголовок
   if ( res_objectsIndexes == null ) {
      firstWrite = true;
      res_objectsCount = 1;
      res_objectsIndexes = new int[1];
      res_objectsOffsets = new int[1];
      headerIndex = 0;
      append = true;
   } else {   // иначе заголовок был прочитан и в нем можно искать запись
      int ind = binarySearchInt(res_objectsIndexes, res_objectsCount, index);
      if ( ind < 0 ) {  // добавление записи
         // смотрим, нет ли выделенной свободной ячейки
         if ( res_objectsCount > 0 && res_objectsIndexes[0] == -1 ) {
            res_objectsIndexes[0] = index;
            headerIndex = res_sortHeaderItem();
            append = false;

         } else {
            append = true;
            int[] tempInd = res_objectsIndexes;
            int[] tempOff = res_objectsOffsets;
            res_objectsCount++;
            res_objectsIndexes = new int[res_objectsCount];
            res_objectsOffsets = new int[res_objectsCount];
            res_objectsIndexes[0] = index;
            for (int i = 0; i < res_objectsCount-1; i++) {
               res_objectsIndexes[i+1] = tempInd[i];
               res_objectsOffsets[i+1] = tempOff[i];
            }
            headerIndex = res_sortHeaderItem();
         }
      } else {          // обновление существующей записи
         headerIndex = ind;
         append = false;
      }
   }
   res_objectsIndexes[headerIndex] = index;

   // если это первое обращение к блоку RMS, надо сначала сохранить заголовок
   if ( firstWrite )
      if ( !res_writeHeader() )
         return false;

   bool result = true;
   RecordStore rs = null;
   try {
      rs = RecordStore.openRecordStore(RES_STORAGE_NAME, true);
      if ( append ) {      // добавление записи
         res_objectsOffsets[headerIndex] = rs.addRecord(rec, 0, rec.length);
      } else {             // изменение существующей записи
         rs.setRecord(res_objectsOffsets[headerIndex], rec, 0, rec.length);
      }
   } catch ( RecordStoreException rse ) { result = false; }
   if ( rs != null )
      try {
         rs.closeRecordStore();
      } catch ( RecordStoreException rse ) { result = false; }

   if ( ! result )
      return false;

   if ( append )
      return res_writeHeader();

   return true;
}



// удаляет элемент из блока RMS
static final bool res_removeRecord(int index) {
   // пытаемся считать заголовок, если он еще не загружен
   if ( res_objectsIndexes == null )
      if ( !res_readHeader() )
         return false;

   // ищем элемент в блоке
   int ind = binarySearchInt(res_objectsIndexes, res_objectsCount, index);
   if ( ind < 0 )
      return false;
   int recId = res_objectsOffsets[ind];

   // удаляем элемент из RMS
   bool result = true;
   RecordStore rs = null;
   try {
      rs = RecordStore.openRecordStore(RES_STORAGE_NAME, true);
      rs.setRecord(recId, new byte[1], 0, 1);
//      rs.deleteRecord(recId);
   } catch ( RecordStoreException rse ) { result = false; }

   if ( !result )
      return false;

   if ( rs != null )
      try {
         rs.closeRecordStore();
      } catch ( RecordStoreException rse ) { }

   // перепаковываем заголовок
/*
   int[] tempInd = res_objectsIndexesRMS[blockIndex];
   int[] tempOff = res_objectsOffsetsRMS[blockIndex];
   res_objectsCountRMS[blockIndex]--;
   res_objectsIndexesRMS[blockIndex] = new int[res_objectsCountRMS[blockIndex]];
   res_objectsOffsetsRMS[blockIndex] = new int[res_objectsCountRMS[blockIndex]];
   int j = 0;
   for (int i = 0; i <= res_objectsCountRMS[blockIndex]; i++) {
      if ( i != ind ) {
         res_objectsIndexesRMS[blockIndex][j] = tempInd[i];
         res_objectsOffsetsRMS[blockIndex][j++] = tempOff[i];
      }
   }
*/
   for (int i = ind; i > 0; i--) {
     res_objectsIndexes[i] = res_objectsIndexes[i-1];
     res_objectsOffsets[i] = res_objectsOffsets[i-1];
   }
   res_objectsIndexes[0] = -1;
   res_objectsOffsets[0] = recId;
   return res_writeHeader();
}



// проверяет существование ресурса в блоке
public static final bool res_isResourceExist(int index) {
   if ( res_objectsIndexes == null )
      if ( !res_readHeader() )
         return false;
   if ( res_objectsIndexes != null )
      if ( binarySearchInt(res_objectsIndexes, res_objectsCount, index) >= 0 )
         return true;
   return false;
}




