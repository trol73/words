#!/usr/bin/python
# -*- coding: utf-8 -*-

# формат файла пака:
#

#	DWORD версия формата файла пака
#	DWORD uid сборки
#	DWORD число слов в паке
#		WORD число символов в слове (юникод)
#			WORD символы слова
#		DWORD абсолютное смещение слова в файле
#
#	область данных wav-ок

import os, sys, glob, zipfile

VERSION = 1
UID = 1

def writeByte(b):
	global packFile
	packFile.write("%c" % b)
	
def writeWord(w):
	writeByte(w & 0xFF)
	writeByte((w >> 8) & 0xFF)
	
def writeDword(dw):
	writeByte(dw & 0xFF)
	writeByte((dw >> 8) & 0xFF)
	writeByte((dw >> 16) & 0xFF)	
	writeByte((dw >> 24) & 0xFF)	
	
def writeChar(w):
	writeByte((w >> 8) & 0xFF)
	writeByte(w & 0xFF)
	
	
def extractWord(fileName):
	name = os.path.basename(fileName)
	word = os.path.splitext(name)[0]
	word = word.replace('.', '').replace('!', '').lower()
	word = unicode(word, 'utf-8').lower()
	return word
	

def tempPackedFileName(fileName):
	return fileName + '.packed'


if len(sys.argv) != 2 and len(sys.argv) != 3:
	print "usage: sound-pack.py <sounds folder> [<packfilename>]"
	sys.exit(1)
	
dirName = sys.argv[1]

packFileName = os.path.basename(dirName) + '.pak'
if len(sys.argv) == 3:
	packFileName = sys.argv[2]




# получаем список файлов и вычисляем размер заголовка
files = []
headerSize = 4+4+4
for infile in glob.glob( os.path.join(dirName + '/', '*.ogg') ):
	files.append(infile)
	word = extractWord(infile)
#	print word, len(word)
	headerSize += 2 + len(word)*2 + 4
	
#print "%x" % headerSize
#print headerSize
	
# сортируем список файлов
files = sorted(files)


packFile = open(packFileName, 'wb')


# сохраняем заголовок
pos = headerSize
writeDword(VERSION)
writeDword(UID)
writeDword(len(files))

for infile in files:
	name = os.path.basename(infile)	
	word = word = extractWord(infile)
#	print '> ', word, len(word)
	writeWord(len(word))
	
	for c in word:
		writeChar(ord(c))
	
	writeDword(pos)
	
	# пакуем файл
	#os.system('java ZipCompressor pack ' + infile + ' ' + tempPackedFileName(infile))
	#pos += os.path.getsize(tempPackedFileName(infile))
	pos += os.path.getsize(infile)


# сохраняем область данных
for infile in files:
	#f = open(tempPackedFileName(infile))
	f = open(infile)
	for d in f:
		packFile.write(d)
	f.close()
	#os.remove(tempPackedFileName(infile))


packFile.close()


sys.exit(0)
