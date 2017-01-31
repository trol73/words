#ifnotdef __SMS_H__
#define   __SMS_H__
#defineblock begin
//----------------------------------------------------------------------------//
//                       Tr Java Mobile Builder v 1.5                         //
//                        Runtime libraries:  SMS.H                           //
//                  Copyright (c) O.A. Trifonov, 2005                         //
//                                Version 1.01                                //
//                                                                            //
//  Defines:                                                                  //
//  Macroses:                                                                 //
//                                                                            //
//                                                                            //
//                                                                            //
//  Supported devices (total 12 types):                                       //
//                                                                            //
//    Motorola      V300/V400/V500, T720, C650                                //
//                                                                            //
//    SonyEricsson  T610                                                      //
//                                                                            //
//    Nokia         Series 40, Series 60                                      //
//                                                                            //
//    Samsung       E700, X600                                                //
//                                                                            //
//    Siemens       55                                                        //
//                                                                            //
//    Siemens       65                                                        //
//                                                                            //
//    Abstract MIDP 1.0 device                                                //
//                                                                            //
//    Abstract MIDP 2.0 device                                                //
//                                                                            //
//----------------------------------------------------------------------------//

//------------------------------------------------------------------------------
#defineblock end
#ifdef JSR_120
import javax.wireless.messaging.*;
#elseif SIEMENS_55
import com.siemens.mp.gsm.sms;
#endif
#endif
