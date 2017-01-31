#ifnotdef __HTTP_H__
#define   __HTTP_H__
#defineblock begin
//----------------------------------------------------------------------------//
//                       Tr Java Mobile Builder v 1.0.                        //
//                        Runtime libraries:  HTTP.H                          //
//                  Copyright (c) O.A. Trifonov, 2005                         //
//                                Version 1.0                                 //
//                                                                            //
//  Defines:                                                                  //
//  Macroses:                                                                 //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//                                                                            //
//    Данный файл содержит определения и функции, которые используются при    //
//  работе с соединениями по протоколу HTTP                                   //
//                                                                            //
//----------------------------------------------------------------------------//

// ----------------------------------------------------------------------------
// КОНСТАНТЫ КОДОВ HTTP
// методы запросов
#define      HTTP_POST                   HttpConnection.POST
#define      HTTP_GET                    HttpConnection.GET
#define      HTTP_HEAD                   HttpConnection.HEAD

// коды ошибок
// 202: The request has been accepted for processing, but the processing has not been completed.
#define      HTTP_ACCEPTED               HttpConnection.HTTP_ACCEPTED
// 502: The server, while acting as a gateway or proxy, received an invalid response from the upstream server it accessed in attempting to fulfill the request.
#define      HTTP_BAD_GATEWAY            HttpConnection.HTTP_BAD_GATEWAY
// 405: The method specified in the Request-Line is not allowed for the resource identified by the Request-URI.
#define      HTTP_BAD_METHOD             HttpConnection.HTTP_BAD_METHOD
// 400: The request could not be understood by the server due to malformed syntax.
#define      HTTP_BAD_REQUEST            HttpConnection.HTTP_BAD_REQUEST
// 408: The client did not produce a request within the time that the server was prepared to wait.
#define      HTTP_CLIENT_TIMEOUT         HttpConnection.HTTP_CLIENT_TIMEOUT
// 409: The request could not be completed due to a conflict with the current state of the resource.
#define      HTTP_CONFLICT               HttpConnection.HTTP_CONFLICT
// 201: The request has been fulfilled and resulted in a new resource being created.
#define      HTTP_CREATED                HttpConnection.HTTP_CREATED
// 413: The server is refusing to process a request because the request entity is larger than the server is willing or able to process.
#define      HTTP_ENTITY_TOO_LARGE       HttpConnection.HTTP_ENTITY_TOO_LARGE
// 417: The expectation given in an Expect request-header field could not be met by this server, or, if the server is a proxy, the server has unambiguous evidence that the request could not be met by the next-hop server.
#define      HTTP_EXPECT_FAILED          HttpConnection.HTTP_EXPECT_FAILED
// 403: The server understood the request, but is refusing to fulfill it.
#define      HTTP_FORBIDDEN              HttpConnection.HTTP_FORBIDDEN
// 504: The server, while acting as a gateway or proxy, did not receive a timely response from the upstream server specified by the URI or some other auxiliary server it needed to access in attempting to complete the request.
#define      HTTP_GATEWAY_TIMEOUT        HttpConnection.HTTP_GATEWAY_TIMEOUT
// 410: The requested resource is no longer available at the server and no forwarding address is known.
#define      HTTP_GONE                   HttpConnection.HTTP_GONE
// 500: The server encountered an unexpected condition which prevented it from fulfilling the request.
#define      HTTP_INTERNAL_ERROR         HttpConnection.HTTP_INTERNAL_ERROR
// 411: The server refuses to accept the request without a defined Content- Length.
#define      HTTP_LENGTH_REQUIRED        HttpConnection.HTTP_LENGTH_REQUIRED
// 301: The requested resource has been assigned a new permanent URI and any future references to this resource SHOULD use one of the returned URIs.
#define      HTTP_MOVED_PERM             HttpConnection.HTTP_MOVED_PERM
// 302: The requested resource resides temporarily under a different URI.
#define      HTTP_MOVED_TEMP             HttpConnection.HTTP_MOVED_TEMP
// 300: The requested resource corresponds to any one of a set of representations, each with its own specific location, and agent- driven negotiation information is being provided so that the user (or user agent) can select a preferred representation and redirect its request to that location.
#define      HTTP_MULT_CHOICE            HttpConnection.HTTP_MULT_CHOICE
// 204: The server has fulfilled the request but does not need to return an entity-body, and might want to return updated meta-information.
#define      HTTP_NO_CONTENT             HttpConnection.HTTP_NO_CONTENT
// 406: The resource identified by the request is only capable of generating response entities which have content characteristics not acceptable according to the accept headers sent in the request.
#define      HTTP_NOT_ACCEPTABLE         HttpConnection.HTTP_NOT_ACCEPTABLE
// 203: The returned meta-information in the entity-header is not the definitive set as available from the origin server.
#define      HTTP_NOT_AUTHORITATIVE      HttpConnection.HTTP_NOT_AUTHORITATIVE
// 404: The server has not found anything matching the Request-URI.
#define      HTTP_NOT_FOUND              HttpConnection.HTTP_NOT_FOUND
// 501: The server does not support the functionality required to fulfill the request.
#define      HTTP_NOT_IMPLEMENTED        HttpConnection.HTTP_NOT_IMPLEMENTED
// 304: If the client has performed a conditional GET request and access is allowed, but the document has not been modified, the server SHOULD respond with this status code.
#define      HTTP_NOT_MODIFIED           HttpConnection.HTTP_NOT_MODIFIED
// 200: The request has succeeded.
#define      HTTP_OK                     HttpConnection.HTTP_OK
// 206: The server has fulfilled the partial GET request for the resource.
#define      HTTP_PARTIAL                HttpConnection.HTTP_PARTIAL
// 402: This code is reserved for future use.
#define      HTTP_PAYMENT_REQUIRED       HttpConnection.HTTP_PAYMENT_REQUIRED
// 412: The precondition given in one or more of the request-header fields evaluated to false when it was tested on the server.
#define      HTTP_PRECON_FAILED          HttpConnection.HTTP_PRECON_FAILED
// 407: This code is similar to 401 (Unauthorized), but indicates that the client must first authenticate itself with the proxy.
#define      HTTP_PROXY_AUTH             HttpConnection.HTTP_PROXY_AUTH
// 414: The server is refusing to service the request because the Request-URI is longer than the server is willing to interpret.
#define      HTTP_REQ_TOO_LONG           HttpConnection.HTTP_REQ_TOO_LONG
// 205: The server has fulfilled the request and the user agent SHOULD reset the document view which caused the request to be sent.
#define      HTTP_RESET                  HttpConnection.HTTP_RESET
// 303: The response to the request can be found under a different URI and SHOULD be retrieved using a GET method on that resource.
#define      HTTP_SEE_OTHER              HttpConnection.HTTP_SEE_OTHER
// 307: The requested resource resides temporarily under a different URI.
#define      HTTP_TEMP_REDIRECT          HttpConnection.HTTP_TEMP_REDIRECT
// 401: The request requires user authentication.
#define      HTTP_UNAUTHORIZED           HttpConnection.HTTP_UNAUTHORIZED
// 503: The server is currently unable to handle the request due to a temporary overloading or maintenance of the server.
#define      HTTP_UNAVAILABLE            HttpConnection.HTTP_UNAVAILABLE
// 416: A server SHOULD return a response with this status code if a request included a Range request-header field , and none of the range-specifier values in this field overlap the current extent of the selected resource, and the request did not include an If-Range request-header field.
#define      HTTP_UNSUPPORTED_RANGE      HttpConnection.HTTP_UNSUPPORTED_RANGE
// 415: The server is refusing to service the request because the entity of the request is in a format not supported by the requested resource for the requested method.
#define      HTTP_UNSUPPORTED_TYPE       HttpConnection.HTTP_UNSUPPORTED_TYPE
// 305: The requested resource MUST be accessed through the proxy given by the Location field.
#define      HTTP_USE_PROXY              HttpConnection.HTTP_USE_PROXY
// 505: The server does not support, or refuses to support, the HTTP protocol version that was used in the request message.
#define      HTTP_VERSION                HttpConnection.HTTP_VERSION

// ----------------------------------------------------------------------------
//  void createConnection(String url)
// открывает HTTP соединение с заданным url
#macro createConnection(url)
httpConnection = (HttpConnection) Connector.open(url);
#endmacro
// ----------------------------------------------------------------------------
//  void setRequestProperty(String name, String value)
// задает свойство соединения
#macro setRequestProperty(name, value)
httpConnection.setRequestProperty(name, value)
#endmacro
// ----------------------------------------------------------------------------
//  void setRequestMethod(String metod)
// задает метод запроса
#macro setRequestMethod(metod)
httpConnection.setRequestMethod(metod)
#endmacro
// ----------------------------------------------------------------------------
//  int getResponseCode()
// возвращает код ответа
#macro getResponseCode()
httpConnection.getResponseCode()
#endmacro
// ----------------------------------------------------------------------------
//  void httpOpenOutputStream()
// открывает поток вывода HTTP
#macro httpOpenOutputStream()
dataOutputStream = httpConnection.openDataOutputStream();
#endmacro
// ----------------------------------------------------------------------------
//  void httpOpenInputStream()
// открывает поток ввода HTTP
#macro httpOpenInputStream()
dataInputStream = httpConnection.openDataInputStream();
#endmacro
// ----------------------------------------------------------------------------
#defineblock end
#endif
