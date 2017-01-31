#ifnotdef __MVL_UI_JAVA_TEXTTOOLS_H__
#define   __MVL_UI_JAVA_TEXTTOOLS_H__
#defineblock begin
/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                         User interface texttools unit


                      Copyright (c) O.A. Trifonov, 2007
                                  Version 1.02

\*----------------------------------------------------------------------------*/

// типы букв
#define _MVL_TXTT_CH_UNKNOWN        0
#define _MVL_TXTT_CH_CONSONANT      1
#define _MVL_TXTT_CH_VOWEL          2
#define _MVL_TXTT_CH_SPECIAL        3
  
  
#defineblock end

public static final String stringSyllableAnalyse(String aStr, char aDelim) {
// раскладывает полученную строку на слоги, вставляя разделители aDelim
  StringBuffer result = new StringBuffer();
  int len = aStr.length();
  if ( len == 0)
    return result.toString();
  // массив типов символов
  byte[] charTypes = new byte[len];
  for (int i = 0; i < len; i++) {
    char ch = aStr.charAt(i);
    if ( txttStrConsonant.indexOf(ch) >= 0 )
      charTypes[i] = _MVL_TXTT_CH_CONSONANT;
    else if ( txttStrVowel.indexOf(ch) >= 0 )
      charTypes[i] = _MVL_TXTT_CH_VOWEL;
    else if ( txttStrSpecial.indexOf(ch) >= 0 )
      charTypes[i] = _MVL_TXTT_CH_SPECIAL;
#ifdef CUSTOM_ZERRO
    else
      charTypes[i] = _MVL_TXTT_CH_UNKNOWN;
#endif
  }

  // собственно расстановка переносов
  int charInWord = 0;    // номер буквы в текущем слове
  int lock = 0;          // счетчик блокировок

  for (int sourcePos = 0; sourcePos < len; sourcePos++) {
    result.append(aStr.charAt(sourcePos));

    // если это последний слог, то его уже не делим
    if ( sourcePos >= len-2)
      continue;
    // если это не буква, то после текущего символа можно ожидать новое слово
    if ( charTypes[sourcePos] == _MVL_TXTT_CH_UNKNOWN ) {
      charInWord = 0;
      continue;
    } else
      charInWord++;      // иначе, мы сейчас читаем слово

    // если слог был закончен, и это первый символ следующего или разделитель, то продолжаем
    if ( lock != 0 ) {
      lock--;
      continue;
    }

    // если сейчас читается не слово или это первый символ слова, то продолжаем
    if ( charInWord <= 1 )
      continue;

    bool isSlogMore = false;  // флаг того, что текущее слово содержит еще хотя бы один слог
    for (int i = sourcePos+1; i < len-1; i++) {
      if ( charTypes[i] == _MVL_TXTT_CH_UNKNOWN )
        break;
      if ( (charTypes[i] == _MVL_TXTT_CH_VOWEL) && ( (charTypes[i+1] != _MVL_TXTT_CH_UNKNOWN) || (i != sourcePos+1)) ) {
        isSlogMore = true;
        break;
      }
    };
    if ( !isSlogMore )
      continue;

    if ( ( (charTypes[sourcePos] == _MVL_TXTT_CH_CONSONANT) && (charTypes[sourcePos-1] == _MVL_TXTT_CH_VOWEL) && (charTypes[sourcePos+1] == _MVL_TXTT_CH_CONSONANT) && (charTypes[sourcePos+2] != _MVL_TXTT_CH_SPECIAL) )
      || ( (charTypes[sourcePos] == _MVL_TXTT_CH_VOWEL) && (charTypes[sourcePos-1] == _MVL_TXTT_CH_CONSONANT) && (charTypes[sourcePos+1] == _MVL_TXTT_CH_CONSONANT) && (charTypes[sourcePos+2] == _MVL_TXTT_CH_VOWEL) )
      || ( (charTypes[sourcePos] == _MVL_TXTT_CH_VOWEL) && (charTypes[sourcePos-1] == _MVL_TXTT_CH_CONSONANT) && (charTypes[sourcePos+1] == _MVL_TXTT_CH_VOWEL) && (charTypes[sourcePos+2] == _MVL_TXTT_CH_CONSONANT) )
      || ( charTypes[sourcePos] == _MVL_TXTT_CH_SPECIAL ) ) {
        result.append(aDelim);
        lock = 1;
    };
    
  }; // for
  
  charTypes = null;
  return result.toString();
}



public static final void formatString(String aStr, Vector aResult, int aWidth, int aFirstLineWidth, String aDelims, TFont aFont) {
// ----------------------
// функция выполняет перенос текстовой строки, разделяя ее на подстроки так, чтобы
// их графическая ширина не превышала заданной.
// Аргументы:
//   aStr     - исходная строка
//   aResult  - набор строк, в который будет добавлено разбиение
//   aWidth   - максимально допустимая графическая ширина подстроки
//   aFirstLineWidth - максимально допустимая длина 1й подстроки (если используется отступ)
//              если отступ не используется, то можно указать 0 либо aWidth
//   aDelims  - строка, содержащая набор разделителей, на которых можно делать перенос
//   aFont    - шрифт для вычисления графической ширины подстрок
//   aFontWidthCorrect - поправка к ширине символа, которая будет добавляться для каждого символа
// ----------------------
  boolean emptyDelims = aDelims == null || aDelims == "";
  int len = aStr.length()-1;
  int lastDelimIndex = 0;    // на этой позиции строку можно разделить
  int startIndex = 0;        // начало текущей подстроки
  int endIndex = 0;          // конец текущей подстроки
  int stringWidth = 0;       // графическая ширина строки
  int prevDelimIndex = -1;
  char ch;
  if ( aDelims == null )
    aDelims = "";
  // данный алгоритм не умеет обрабатывать ситуации, когда форматируемая строка состоит из одного символа
  if ( aStr.length() <= 1 )
    aResult.addElement(aStr);
  else
  while ( endIndex < len ) {
    if ( stringWidth > ((aFirstLineWidth == 0) ? aWidth : aFirstLineWidth) || endIndex == len-1) {
      // последняя строка абзаца
      if (endIndex == len-1 && startIndex <= len) {
        endIndex = len + 1;
        // если строка по непонятным причиам получилась слишком длинной, то откатываемся к предыдущему символу
        String tstStr = aStr.substring(startIndex, endIndex);
        if ( !emptyDelims )
          tstStr = deleteCharFromString(tstStr, ""+aDelims.charAt(0));
        bool lastError = false;
        if ( getFontStringWidth(aFont, tstStr) > ((aFirstLineWidth == 0) ? aWidth : aFirstLineWidth) ) {
          if ( lastDelimIndex >= 0 )
            endIndex = lastDelimIndex;
            lastError = true;
        }
        stringWidth = 0;
        // для предотвращениязациклевания и исчерпания памяти когда строку нельзя уместить
        if ( startIndex == endIndex && endIndex == 0 ) {
           aResult.addElement(aStr.substring(startIndex));
           break;
        }
        // произошла ошибка связанная с тем, что строка не уместилась в область
        if ( endIndex < startIndex ) {
          if ( aResult.size() == 0 )
             aResult.addElement(aStr);
           else
            aResult.addElement(aStr.substring(startIndex));
          return;
        }
        aResult.addElement(aStr.substring(startIndex, endIndex));  // !!!!
        if ( !lastError )
          break;
        if ( emptyDelims )
          endIndex--;
        startIndex = endIndex;
//        aResult.addElement(aStr.substring(startIndex, len+1));
//          lastDelimIndex = len-1;

        continue;
//        break;
      }
      // если строку пора делить, и позиция для деления найдена, делим по ней
      if ( lastDelimIndex > startIndex ) {
        endIndex = lastDelimIndex;
        // если строка по непонятным причиам получилась слишком длинной, то откатываемся к предыдущему символу
        String tstStr = aStr.substring(startIndex, endIndex);
        if ( !emptyDelims )
          tstStr = deleteCharFromString(tstStr, ""+aDelims.charAt(0));
        if ( getFontStringWidth(aFont, tstStr) > ((aFirstLineWidth == 0) ? aWidth : aFirstLineWidth) ) {
          if ( prevDelimIndex >= 0 )
            endIndex = prevDelimIndex;
        }
        stringWidth = 0;
        aResult.addElement(aStr.substring(startIndex, endIndex));  // !!!!
        if ( emptyDelims )
          endIndex--;
      } else if ( aFirstLineWidth != 0 ) { // не умещается 1я строка с отступом
        aFirstLineWidth = 0;
        startIndex = 0;
        endIndex = 0;
        stringWidth = 0;
        lastDelimIndex = 0;
        continue;
      } else {
        endIndex--;
        stringWidth = 0;
        aResult.addElement(aStr.substring(startIndex, endIndex));
      }
      aFirstLineWidth = 0; // первую строку перенесли
      startIndex = endIndex+1;
    } else {
      endIndex++;
      // если строка умещается
      ch = aStr.charAt(endIndex);
      // если разделители не заданыы, или символ является разделительным
      if ( emptyDelims || aDelims.indexOf(ch) >= 0 ) {
        prevDelimIndex = lastDelimIndex;
        lastDelimIndex = endIndex;
      }
      // если символ не является разделительным маркером
      if ( !emptyDelims && aDelims.indexOf(ch) != 0 )
        stringWidth += getFontCharWidth(aFont, ch);
    }
  } // while

    
/*
  while (endIndex < len) {
    endIndex++;
    // если строка умещается
    ch = aStr.charAt(endIndex);

    if ( stringWidth <= ((aFirstLineWidth == 0) ? aWidth : aFirstLineWidth) ) {
      // если разделители не заданыы, или символ является разделительным
      if ( emptyDelims || aDelims.indexOf(ch) >= 0 ) {
        prevDelimIndex = lastDelimIndex;
        lastDelimIndex = endIndex;
      }
      // если символ не является разделительным маркером
      if ( !emptyDelims && aDelims.indexOf(ch) != 0 )
        stringWidth += getFontCharWidth(aFont, ch);
    } else {
      // если строку пора делить, и позиция для деления найдена, делим по ней
      if ( lastDelimIndex > startIndex ) {
        endIndex = lastDelimIndex;
        
        // если строка по непонятным причиам получилась слишком длинной, то откатываемся к предыдущему символу
        String tstStr = aStr.substring(startIndex, endIndex);
        if ( !emptyDelims )
          tstStr = deleteCharFromString(tstStr, ""+aDelims.charAt(0));
        if ( getFontStringWidth(aFont, tstStr) > ((aFirstLineWidth == 0) ? aWidth : aFirstLineWidth) ) {
          if ( prevDelimIndex >= 0 )
            endIndex = prevDelimIndex;
        }
        
        stringWidth = 0;
        aResult.addElement(aStr.substring(startIndex, endIndex));  // !!!!
        if ( emptyDelims )
          endIndex--;
      } else if ( aFirstLineWidth != 0 ) { // не умещается 1я строка с отступом
        aFirstLineWidth = 0;
        startIndex = 0;
        endIndex = 0;
        stringWidth = 0;
        lastDelimIndex = 0;
        continue;
      } else {
        endIndex--;
        aResult.addElement(aStr.substring(startIndex, endIndex));
      }
      aFirstLineWidth = 0; // первую строку перенесли
      startIndex = endIndex+1;
    }
  } // while

*/

  // выделяем последнюю строку если надо
//  if (startIndex <= len)
//    aResult.addElement(aStr.substring(startIndex, len+1));
//    aResult.addElement("-");

}



public static final String deleteCharFromString(String aStr, String aChars) {
// ----------------------
// возвращает строку, из которой удалены все указанные символы
// Аргументы:
//   aStr     - исходная строка
//   aChars   - символы, которые надо удалить
// Возвраща ет:
//   строку aStr с удаленными символами строки aChars
// ----------------------
  int len = aStr.length();
  StringBuffer result = new StringBuffer();
  for (int i = 0; i < len; i++) {
    char ch = aStr.charAt(i);
    if ( aChars.indexOf(ch) < 0 )
      result.append(ch);
  }
  return result.toString();
}

#endif  // __MVL_UI_JAVA_TEXTTOOLS_H__
