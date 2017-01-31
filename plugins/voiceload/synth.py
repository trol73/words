#!/usr/bin/python
# -*- coding: utf-8 -*-
import os, sys, httplib, urllib, random

worsdStoreDir = 'words-synth'
#proxy='localhost:8080'
proxy=''

ogg_quality = -1
sampleRate = '44100'



lang = 'ru'
_url = "text-to-speech.imtranslator.net"

cookies_general = 'TTSid=264451804; __qca=P0-1586639399-1263725630985; __utma=44670113.514063665.1263725631.1282423015.1282425143.5; z=s; PX=12; sh=3; CLR=f2f2f2; m=2; CLRT=000000; ws=; ASPSESSIONIDASQCSCCT=LNGLCNPDIOMMMIPHHGCOMLED; __utmc=44670113; __utmz=44670113.1282411076.2.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); ASPSESSIONIDQSSAQABR=KDALELAABMEHHJHFEKEHIBBH; ASPSESSIONIDASTCTDDT=IGFOGJBALDFIJIJJEFNCOENG; __utmb=44670113.22.10.1282425143'
cookies_swf = '__qca=P0-1586639399-1263725630985'

_headers = {
'User-Agent': 'Mozilla/5.0 (Windows; U; Windows NT 6.0; ru; rv:1.9.2.8) Gecko/20100722 MRA 5.5 (build 02842) Firefox/3.6.8 (.NET CLR 3.0.30618)',
'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
'Accept-Language': 'ru,en-us;q=0.7,en;q=0.3',
'Accept-Charset': 'windows-1251,utf-8;q=0.7,*;q=0.7',
'Keep-Alive': '115',
'Proxy-Connection': 'keep-alive',
'Cookie': cookies_general
}

_cookies = {}

cookies = {}
header = {}



def test(cond, msg):
	if not cond:
		print "ERROR:", msg
		raise Exception
		#sys.exit(-2)


def httpRequest(method, url, address, args, reqHeaders):
	try: proxy
	except NameError:
		send_url = url
	else:
		if len(proxy) > 0:
			send_url = proxy
		else:
			send_url = url
	conn = httplib.HTTPConnection(send_url)
	if address.find('http://') == 0:
		fullUrl = address
	else:
		fullUrl = 'http://' + url + address
	if len(args) == 0:
		args = ''
	conn.request(method, fullUrl, args, reqHeaders)
	resp = conn.getresponse()
#	print resp.status, resp.reason
	test(resp.status == 200, "invalid request: "+ fullUrl + " [" + str(resp.status) + "]")
	data = resp.read()
	hdrs = resp.getheaders()
	global headers, cookies
	for header in hdrs:
		if header[0] == 'set-cookie':
			lst = header[1].split(';')
			for itm in lst:
				item = itm.replace('path=/,', '').replace('path=/', '').lstrip()
				if len(item.split('=')) < 2:
					continue
				name = item.split('=')[0]
				value = item.split('=')[1]
				cookies[name] = value
	newCookies = ''
	for rec in cookies.keys():
		newCookies += rec + '=' + cookies[rec] + '; '
	#print newCookies
	headers['Cookie'] = newCookies
			
	conn.close()
	
	return data



def decodeWord(word):
	result = ''
	for c in word:
		result += '%' + '%x' % ord(c)
	return result.upper()


def writeToFile(fileName, data):
	f = file(fileName, 'wb')
	f.write(data)
	f.close()
	
def extractHostName(s):
	hostName = s.replace('http://', '')
	pos1 = hostName.find(':')
	pos2 = hostName.find('/')
	if pos1 < pos2 and pos1 > 0:
		hostName = hostName[:pos1]		
	elif pos2 > 0:
		hostName = hostName[:pos2]	
	return hostName
	


def downloadWord(word, lang, directory):
	global worsdStoreDir, proxy, _url, cookies_swf, _headers, _cookies,  headers, cookies
	
	url = _url
	headers = _headers
	cookies = _cookies

	print word

	worsdDir = directory
	wordFile = word.replace('-', ' ').replace('(', ' ').replace(')', ' ').replace(' ', '_').replace('__', '_').replace('"', '')
	wordFileName = worsdDir + '/' + wordFile

	if os.path.exists(wordFileName + '.ogg'):
		return ''
	if os.path.exists(wordFileName + '.wav'):
		return ''
	if os.path.exists(wordFileName + '.mp3'):
		return wordFileName



	if not os.path.exists(worsdDir):
		os.makedirs(worsdDir)

	
	#print word
	decodedWord = decodeWord(word)

	# читаем начальную страницу
	data = httpRequest("GET", url, "/speech.asp?dir=" + lang + "&text=" + decodedWord, {}, headers)

	# ищем вхождение стартового скрипта и выдираем параметры (ul,ID,TTSlang) 
	searchTemplate = 'onLoad="speechBuilder('
	s=''

	pos = data.find(searchTemplate)
	test(pos > 0, '[1]')
	pos += len(searchTemplate)
	posEnd = data.find(')', pos)
	test(posEnd > 0, '[2]')
	s = data[pos: posEnd]

	params = s.split(',')
	test(len(params) == 3, '[3]')
	speechBuilder_ul = params[0][1:-1]
	speechBuilder_ID = params[1][1:-1]
	speechBuilder_TTSlang = params[2][1:-1]
	#print ">>> ", speechBuilder_ul, speechBuilder_ID, speechBuilder_TTSlang

	# теперь постим на сервер текст, который мы собираемся воспроизвести
	headers["Content-Length"] = str(len("text="+decodedWord))
	headers["Content-type"] = "application/x-www-form-urlencoded"
	data = httpRequest("POST", url, "/sockets/box.asp", "text="+decodedWord, headers)
	del headers["Content-Length"]
	del headers["Content-type"]
	#print data


	# теперь шлем запрос из которого узнаем ID swf-ки
	speed = '0'
	ul = speechBuilder_ul
	TTSlang = speechBuilder_TTSlang
	ID = speechBuilder_ID

	if lang == 'ru':
		face = "VoyagerHead"
		voice="Olga"
	elif lang == 'en':
		face = "PeterHead"
		voice = decodeWord("VW Paul")
	elif lang == 'de':
		face = "James"
		voice = "Stefan"

	data = httpRequest("GET", url, "/sockets/tts.asp?speed="+speed+"&url="+ul+"&dir="+TTSlang+"&B=1&ID="+ID+"&chr="+face+"&vc="+voice, {}, headers)

	# на этой странице мы ищем ссылку на swf
	searchTemplate = '<PARAM ID="MOVIE" NAME="MOVIE" VALUE="'
	s=''

	pos = data.find(searchTemplate)
	test(pos >= 0, '[3]')
	pos += len(searchTemplate)
	posEnd = data.find('"', pos)
	test(posEnd > 0, '[4]')
	s = data[pos: posEnd]


	# непонятно, для чего, но надо скачать еще одну страницу
	#data = httpRequest("GET", url, '/COUNTERS/default.asp?SI=TEXT-TO-SPEECH%7CTTS', {}, headers)


	# скачиваем SWF
	headers["Cookie"] = cookies_swf
	data = httpRequest("GET", extractHostName(s), s, {}, headers)

	word = word.replace(' ', '_')
	writeToFile(wordFile + '.swf', data)
	print 'SWF ', wordFile + '.swf'
	# извлекаем mp3
	os.system('swfextract -o "'+wordFileName + '.mp3" -m "' + wordFile + '.swf"')

	# удаляем временные файлы
	#word = word.replace("'", '')
	os.remove(word+'.swf')
	return wordFileName


	#print word

# конвертирует файл mp3 в файл wav
def mp3ToWav(infile, outfile):
	cmd = "lame --silent --decode \"" + infile + "\" \"" + outfile + '"'
	#print cmd
	res = os.system(cmd)
	if res != 0:
		sys.exit(res)
			 

# конвертирует файл wav в ogg
def wavToOgg(infile, outfile, quality):
	global sampleRate
	cmd = 'oggenc \"' + infile + '\" -q ' + str(quality) + ' --quiet '
	if len(sampleRate) >  0:
		cmd += '--resample ' + sampleRate + ' '
	cmd += '-o \"' + outfile + '"'
	#print cmd
	res = os.system(cmd)
	if res != 0:
		sys.exit(res);





def main():
	if len(sys.argv) < 4:
		print "usage: sound-synth.py ru|en <dir> <word>"
		sys.exit(1)
	lang = sys.argv[1]	
	directory = sys.argv[2]
	word = ''
	for i in range(3, len(sys.argv)):
		word += sys.argv[i] + ' '
	word = word.strip()
	wordFileName = downloadWord(word, lang, directory)
	if len(wordFileName) == 0:
		sys.exit(5)
	mp3Name = wordFileName + '.mp3'
	wavName = wordFileName + '.wav'
	oggName = wordFileName + '.ogg'
	mp3ToWav(mp3Name, wavName)
	wavToOgg(wavName, oggName, ogg_quality)
	os.remove(mp3Name)
	os.remove(wavName)
	sys.exit(0)


# When invoked as main program, invoke the profiler on a script
if __name__ == '__main__':
    main()
