#ifnotdef __SOUND_H__
#define   __SOUND_H__
#defineblock begin
//----------------------------------------------------------------------------//
//                       Tr Java Mobile Builder v 1.0.                        //
//                        Runtime libraries: SOUND.H                          //
//                      Copyright (c) O.A. Trifonov, 2004                     //
//                                Version 1.01                                //
//                                                                            //
//  Defines:                                                                  //
//  Macroses:                                                                 //
//  Functions:                                                                //
//  Variables:                                                                //
//                                                                            //
//                                                                            //
//  Supported devices (total 9 types):                                        //
//                                                                            //
//    Motorola      V300/V400/V500, T720, C650                                //
//                                                                            //
//    SonyEricsson  T610, K700                                                //
//                                                                            //
//    Nokia         Series 40, Series 60                                      //
//                                                                            //
//    Samsung       E700, X600                                                //
//                                                                            //
//    Siemens       S55, CX65                                                 //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//                 модуль определяет следующие идентификаторы                 //
//----------------------------------------------------------------------------//
  SOUND_PRESENT        // - для данного устройства есть поддержка звука
//  SOUND_CAN_PRESENT    // - в данной серии устройств имеются модели с поддержкой звука
  NOT_SOUND            // - данное устройство не имеет поддержки звука
  VIBRO_PRESENT        // - для данного устройства есть поддержка вибросигнала
  LIGHT_PRESENT        // - для данного устройства есть поддержка световых эффектов

  SOUND_SUPPORT_MIDI   // - данное устройство может воспроизводить аудиофалы .mid
  SOUND_SUPPORT_MMF    // - данное устройство может воспроизводить аудиофалы .mmf
  SOUND_SUPPORT_WAV    // - данное устройство может воспроизводить аудиофалы .wav

  SOUND                // - название класса аудиоплеера для данного устройства
  SOUND_LOOP_INF       // - константа бесконечного проигрывания звука

//------------------------------------------------------------------------------
//         импортируем библиотечный пакет для заданного устройства            //
//------------------------------------------------------------------------------
#defineblock end
#ifdef    MOTOROLA_V300
import javax.microedition.media.*;
#elseif   MOTOROLA_C650
import javax.microedition.media.*;
#elseif   MOTOROLA_T720
#elseif   SONYERICSSON_T610
import javax.microedition.media.*;
#elseif   SIEMENS_65
import javax.microedition.media.*;
#elseif   SONYERICSSON_K700
import javax.microedition.media.*;
#elseif   NOKIA_SERIES_40
import javax.microedition.media.*;
import com.nokia.mid.sound.Sound;
#elseif   NOKIA_SERIES_60
import javax.microedition.media.*;
import com.nokia.mid.sound.Sound;
#elseif   SAMSUNG_E700
import com.samsung.util.AudioClip;
#elseif   SAMSUNG_X600
import com.samsung.util.AudioClip;
#elseif   SIEMENS_55
import com.siemens.mp.media.*;
#endif
#defineblock begin
//------------------------------------------------------------------------------
//                     определяем звуковые макросы
//------------------------------------------------------------------------------
#ifdef    MOTOROLA_V300

  #define   SOUND_PRESENT
//  VIBRO_PRESENT
//  LIGHT_PRESENT
  #define   SOUND_SUPPORT_MIDI
//  SOUND_SUPPORT_MMF
//  SOUND_SUPPORT_WAV
  #define   SOUND                    Player
  #define   SOUND_LOOP_INF           -1

#elseif   MOTOROLA_T720

  #define   NOT_SOUND
//  VIBRO_PRESENT
//  LIGHT_PRESENT

#elseif   SONYERICSSON_T610

  #define   SOUND_PRESENT
//  VIBRO_PRESENT
//  LIGHT_PRESENT
  #define   SOUND_SUPPORT_MIDI
//  SOUND_SUPPORT_MMF
//  SOUND_SUPPORT_WAV
  #define   SOUND                    Player
  #define   SOUND_LOOP_INF           -1
  
#elseif   SONYERICSSON_K700

  #define   SOUND_PRESENT
//  VIBRO_PRESENT
//  LIGHT_PRESENT
  #define   SOUND_SUPPORT_MIDI
//  SOUND_SUPPORT_MMF
//  SOUND_SUPPORT_WAV
  #define   SOUND                    Player
  #define   SOUND_LOOP_INF           -1


#elseif   NOKIA_SERIES_40

//  #define   SOUND_CAN_PRESENT
//  VIBRO_PRESENT
//  LIGHT_PRESENT
  #define   SOUND_SUPPORT_MIDI
//  SOUND_SUPPORT_MMF
//  SOUND_SUPPORT_WAV
  #define   SOUND                    Player
  #define   SOUND_LOOP_INF           -1

#elseif   NOKIA_SERIES_60

//  #define   SOUND_CAN_PRESENT
//  VIBRO_PRESENT
//  LIGHT_PRESENT
  #define   SOUND_SUPPORT_MIDI
//  SOUND_SUPPORT_MMF
//  SOUND_SUPPORT_WAV
  #define   SOUND                    Player
  #define   SOUND_LOOP_INF           -1

#elseif   SAMSUNG_E700

  #define   SOUND_PRESENT
//  VIBRO_PRESENT
//  LIGHT_PRESENT
  #define  SOUND_SUPPORT_MMF
//  SOUND_SUPPORT_WAV
  #define   SOUND                    AudioClip
  #define   SOUND_LOOP_INF           255

#elseif   SAMSUNG_X600

  #define   SOUND_PRESENT
//  VIBRO_PRESENT
//  LIGHT_PRESENT
  #define   SOUND_SUPPORT_MMF
//  SOUND_SUPPORT_WAV
  #define   SOUND                    AudioClip
  #define   SOUND_LOOP_INF           255

#elseif   SIEMENS_55

  #define   SOUND_PRESENT
//  VIBRO_PRESENT
//  LIGHT_PRESENT
  #define   SOUND_SUPPORT_MIDI
//  SOUND_SUPPORT_MMF
//  SOUND_SUPPORT_WAV
  #define   SOUND                    Player
  #define   SOUND_LOOP_INF           100
  
#elseif    SIEMENS_65

  #define   SOUND_PRESENT
//  VIBRO_PRESENT
//  LIGHT_PRESENT
  #define   SOUND_SUPPORT_MIDI
//  SOUND_SUPPORT_MMF
//  SOUND_SUPPORT_WAV
  #define   SOUND                    Player
  #define   SOUND_LOOP_INF           -1


#endif

#defineblock end
