#ifnotdef __RMS_H__
#define   __RMS_H__
#defineblock begin
//----------------------------------------------------------------------------//
//                       Tr Java Mobile Builder v 1.0.                        //
//                        Runtime libraries: RMS.H                            //
//                      Copyright (c) O.A. Trifonov, 2004                     //
//                                Version 1.01                                //
//                                                                            //
//  Defines:    0                                                             //
//  Macroses:   19                                                            //
//  Functions:  0                                                             //
//  Variables:  0                                                             //
//                                                                            //
//                                                                            //
//  Supported devices (total 8 types):                                        //
//                                                                            //
//    Motorola      V300/V400/V500, T720                                      //
//                                                                            //
//    SonyEricsson  T610                                                      //
//                                                                            //
//    Nokia         Series 40, Series 60                                      //
//                                                                            //
//    Samsung       E700, X600                                                //
//                                                                            //
//    Siemens       S55                                                       //
//                                                                            //
//----------------------------------------------------------------------------//

//------------------------------------------------------------------------------
//              ОТКРЫТИЕ, СОЗДАНИЕ И ЗАКРЫТИЕ ХРАНИЛИЩА                       //
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//   void createRMS(String name)
// создает хранилище RMS с именем name если оно еще не создано, иначе, открывает
// его на запись
#macro createRMS(name)
// создаем хранилище и потоки
RecordStore recordStore = null;
try {
  recordStore = RecordStore.openRecordStore(name, true);
  byte roBuf[] = null;
  try {
    ByteArrayOutputStream rByteOutputStream = new ByteArrayOutputStream();
    DataOutputStream rDataOutputStream = new DataOutputStream(rByteOutputStream);
#define    __RMS_USED_CREATE_PROC__
#undefine  __RMS_USED_OPEN_PROC__
#endmacro
//------------------------------------------------------------------------------
//   void openRMS(String name)
// открывает хранилище RMS для чтения
#macro openRMS(name)
RecordStore recordStore = null;
try {
// открываем хранилище и связываем с ним потоки ввода
  recordStore = RecordStore.openRecordStore(name, true);
  byte riBuf[] = recordStore.getRecord(1);
  if(riBuf != null)
    try {
      ByteArrayInputStream rByteInputStream = new ByteArrayInputStream(riBuf);
      DataInputStream rDataInputStream = new DataInputStream(rByteInputStream);
#define    __RMS_USED_OPEN_PROC__
#undefine  __RMS_USED_CREATE_PROC__
#endmacro
//------------------------------------------------------------------------------
//   void closeRMS()
// закрывает хранилище RMS. Если хранилище было открыто/создано для записи, то
// выполняет запись буфферов.
#macro closeRMS()
#ifdef __RMS_USED_CREATE_PROC__               // закрытие RMS после создания
    roBuf = rByteOutputStream.toByteArray();
    rDataOutputStream.close(); 
    rByteOutputStream = null;  // зануляем потоки
    rDataOutputStream = null;
  #ifdef DEBUG
  } catch(IOException ioe) { System.out.println(">> FATAL ERROR! >> closeRMS() [1.1] -> " + ioe.toString()); }
  #else
  } catch(IOException ioe) { }
  #endif
  // создаем первую запись или изменяем существующую
  if(recordStore.getNumRecords() == 0) recordStore.addRecord(roBuf, 0, roBuf.length);
  else recordStore.setRecord(1, roBuf, 0, roBuf.length);
  roBuf = null;
  #ifdef DEBUG
} catch(RecordStoreException rse) { System.out.println(">> FATAL ERROR! >> closeRMS() [1.2] -> " + rse.toString()); }
  #else
} catch(RecordStoreException rse) { }
  #endif
// закрываем хранилище
if(recordStore != null) {
  #ifdef DEBUG
  try { recordStore.closeRecordStore(); } catch (RecordStoreException rse) { System.out.println(">> FATAL ERROR! >> closeRMS() [1.3] -> " + rse.toString()); }
  #else
  try { recordStore.closeRecordStore(); } catch (RecordStoreException rse) { }
  #endif
  recordStore = null;
}
#elseif __RMS_USED_OPEN_PROC__                // закрытие RMS после открытия
      rDataInputStream.close();
      // зануляем все использованные объекты
      rByteInputStream = null;
      rDataInputStream = null;
      riBuf = null;
  #ifdef DEBUG
    } catch(IOException ioe) { System.out.println(">> FATAL ERROR! >> closeRMS() [2.1] -> " + ioe.toString()); }
} catch(RecordStoreException rse) { System.out.println(">> FATAL ERROR! >> closeRMS() [2.2] -> " + rse.toString()); }
  #else
    } catch(IOException ioe) { }
} catch(RecordStoreException rse) { }
  #endif
if (recordStore != null) {
  #ifdef DEBUG
  try { recordStore.closeRecordStore(); } catch (RecordStoreException rse) { System.out.println(">> FATAL ERROR! >> closeRMS() [2.3] -> " + rse.toString()); }
  #else
  try { recordStore.closeRecordStore(); } catch (RecordStoreException rse) { }
  #endif
  recordStore = null;
}
#endif                                        // закрытие после открытия
#endmacro
//------------------------------------------------------------------------------
//                        ЗАПИСЬ ДАННЫХ В ХРАНИЛИЩЕ                           //
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//   void rWriteByte(byte v)
// сохраняет байт в хранилище                       (1 байт)
#macro rWriteByte(v)
    rDataOutputStream.writeByte(v)
#endmacro
//------------------------------------------------------------------------------
//   void rWriteChar(char v)
// сохраняет символ в хранилище                     (2 байта)
#macro rWriteChar(v)
    rDataOutputStream.writeChar(v)
#endmacro
//------------------------------------------------------------------------------
//   void rWriteBool(boolean v)
// сохраняет логическую переменную в хранилище      (1 байт)
#macro rWriteBool(v)
    rDataOutputStream.writeBoolean(v)
#endmacro
//------------------------------------------------------------------------------
//   void rWriteInt(integer v)
// сохраняет целое в хранилище                      (4 байта, первый-старший)
#macro rWriteInt(v)
    rDataOutputStream.writeInt(v)
#endmacro
//------------------------------------------------------------------------------
//   void rWriteLong(long v)
// сохраняет длинное целое в хранилище              (8 байт, первый-старший)
#macro rWriteLong(v)
    rDataOutputStream.writeLong(v)
#endmacro
//------------------------------------------------------------------------------
//   void rWriteShort(int v)
// сохраняет короткое целое в хранилище             (2 байта, первый-старший)
#macro rWriteShort(v)
    rDataOutputStream.writeShort(v)
#endmacro
//------------------------------------------------------------------------------
//   void rWriteString(String v)
// сохраняет строку как массив символов (последовательно вызывая rWriteChar())
#macro rWriteString(v)
    rDataOutputStream.writeShort(__void__macro__(v).length());
    rDataOutputStream.writeChars(v)
#endmacro
//------------------------------------------------------------------------------
//   void rWriteUTF(String v)
// сохраняет строку в формате UTF-8 (сначала 2 байта длины блока (не строки!),
// затем - кодированную строку)
#macro rWriteUTF(v)
    rDataOutputStream.writeUTF(v)
#endmacro
//------------------------------------------------------------------------------
//                    ЧТЕНИЕ ДАННЫХ ИЗ ХРАНИЛИЩА                              //
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//   byte rReadByte()
// читает байт из хранилища                         (1 байт)
#macro rReadByte(v)
      v = rDataInputStream.readByte()
#endmacro
//------------------------------------------------------------------------------
//   char rReadChar()
// читает символ из хранилища                       (2 байта)
#macro rReadChar(v)
      v = rDataInputStream.readChar()
#endmacro
//------------------------------------------------------------------------------
//   bool rReadBool()
// читает логическую переменную из хранилища        (1 байт)
#macro rReadBool(v)
      v = rDataInputStream.readBoolean()
#endmacro
//------------------------------------------------------------------------------
//   int rReadInt()
// читает целое из хранилища                        (4 байта, первый-старший)
#macro rReadInt(v)
      v = rDataInputStream.readInt()
#endmacro
//------------------------------------------------------------------------------
//   long rReadLong()
// читает длинное целое из хранилища                (8 байт, первый-старший)
#macro rReadLong(v)
      v = rDataInputStream.readLong()
#endmacro
//------------------------------------------------------------------------------
//   short rReadShort()
// читает короткое целое из хранилища               (2 байта, первый-старший)
#macro rReadShort(v)
      v = rDataInputStream.readShort()
#endmacro
//------------------------------------------------------------------------------
//   String rReadString()
// читает строку как массив символов (последовательно вызывая rReadChar())
#macro rReadString(v)
		v = new String();
		for (int i = rDataInputStream.readShort(); i > 0; i--)
		  v = v + rDataInputStream.readChar();
#endmacro
//------------------------------------------------------------------------------
//   String rReadUTF()
// читает строку в формате UTF-8 (сначала 2 байта длины блока (не строки!),
// затем - кодированную строку)
#macro rReadUTF(v)
      v = rDataInputStream.readUTF()
#endmacro
//------------------------------------------------------------------------------


#defineblock end
#endif                  // __RMS_H__
