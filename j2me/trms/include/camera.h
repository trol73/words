#ifnotdef __CAMERA_H__
#define   __CAMERA_H__
#defineblock begin
//----------------------------------------------------------------------------//
//                       Tr Java Mobile Builder v 1.5.                        //
//                        Runtime libraries: CAMEA.H                          //
//                      Copyright (c) O.A. Trifonov, 2005                     //
//                                Version 1.0                                 //
//                                                                            //
//                 MMAPI 1.1 (JSR 135) camera support unit                    //
//                                                                            //
//  Defines:                                                                  //
//  Macroses:                                                                 //
//  Functions:                                                                //
//  Variables:                                                                //
//                                                                            //
//                                                                            //
//----------------------------------------------------------------------------//

#defineblock end
#ifdef    JSR135
import javax.microedition.media.control.*;
#endif
#defineblock begin
//-----------------------------------------------------------------------------
// String mmapiVersion(void)
// Return: version of the MMAPI specification
#macro mmapiVersion()
System.getProperty("microedition.media.version")
#endmacro

//-----------------------------------------------------------------------------
// bool mmapiVideoCaptureSupport(void)
// Return: true if video capture is supported
#macro mmapiVideoCaptureSupport()
(System.getProperty("supports.video.capture") == "true")
#endmacro

//-----------------------------------------------------------------------------
// bool mmapiRecordingSupport(void)
// Return: true if recording is supported
#macro mmapiRecordingSupport()
(System.getProperty("supports.recording") == "true")
#endmacro

//-----------------------------------------------------------------------------
// String mmapiGetVideoEncodings(void)
// Return: specifies the supported capture video formats
/*
 video_encodings   = video_enc_param *( "&" video_param )
     video_enc_param   = "encoding=" video_enc
     video_enc         = "gray8" / "rgb888" / "bgr888" /
                         "rgb565" / "rgb555" / "yuv444" /
                         "yuv422" / "yuv420" / "jpeg" / "png" /
                         content_type
     video_param       = "width=" width /
                         "height=" height /
                         "fps=" fps /
                         "colors=" colors /
                         "progressive=" progressive /
                         "interlaced=" interlaced /
                         "type=" video_type
     width             = pos_integer
     height            = pos_integer
     fps               = pos_number
     quality           = pos_integer
     colors            = "p" colors_in_palette /
                       = "rgb" r_bits g_bits b_bits /
                       = "gray" gray_bits
     colors_in_palette = pos_integer
     r_bits            = pos_integer
     g_bits            = pos_integer
     b_bits            = pos_integer
     gray_bits         = pos_integer
     progressive       = boolean
     video_type        = jfif / exif / other_type
     other_type        = alphanumeric
     interlaced        = boolean
     pos_number        = 1*DIGIT [ "." 1*DIGIT ]
     boolean           = "true" / "false"
*/
#macro mmapiGetVideoEncodings()
System.getProperty("video.encodings")
#endmacro

//-----------------------------------------------------------------------------
// String mmapiGetVideosnapshotEncodings(void)
// Return: specifies the supported capture video formats
#macro mmapiGetVideoSnapshotEncodings()
(System.getProperty("video.snapshot.encodings"))
#endmacro



//-----------------------------------------------------------------------------
#defineblock end
#endif // __CAMERA_H__
