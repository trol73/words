#ifnotdef __MVL_UI_JAVA_CONSTS_H__
#define   __MVL_UI_JAVA_CONSTS_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                     User interface static constants unit


                      Copyright (c) O.A. Trifonov, 2007
                                  Version 1.0

\*----------------------------------------------------------------------------*/
#defineblock end

// гласные буквы русского языка, отсортированные по частоте употребления
private static final String txttStrVowelRus = "оеаиуяйюэОАИЯЭЕУЮЙ";

// гласные буквы английского языка, отсортированные по частоте употребления
private static final String txttStrVowelLat = "eoaiuAOIEUJj";

// гласные буквы, отсортированные по частоте употребления
private static final String txttStrVowel = txttStrVowelRus + txttStrVowelLat;

// согласные буквы русского языка, отсортированные по частоте употребления
private static final String txttStrConsonantRus = "тнслврмкдпгбзчжшхцщНВПфСКМФДTБЛГРЧЗХШЖЦЩ";

// согласные буквы английского языка, отсортированные по частоте употребления
private static final String txttStrConsonantLat = "trsnlcdTmhSRNbpyfCFPgDMwvLXkBWKGHxVzqYZQ";

// согласные буквы, отсортированные по частоте употребления
private static final String txttStrConsonant = txttStrConsonantRus + txttStrConsonantLat;

// особые символы русского алфавита для разложения слов на слоги
private static final String txttStrSpecial = "ьыъЫЬЪ";


#endif // __MVL_UI_JAVA_CONSTS_H__
