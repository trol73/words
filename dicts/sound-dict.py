#!/usr/bin/python
# -*- coding: utf-8 -*-

# копирует все звуковые файлы для словаря
import os, sys, shutil


# обрабатывает слово. lang = 'en'/'ru'
def processWord(word, lang):
	word = word.replace(' ', '_')
	outfile = toDir + '-' + lang + '/' + word + '.ogg'
	if os.path.exists(outfile):
		return
	infile = fromDir + '-' + lang + '/' + word + '.ogg'
	if os.path.exists(infile):
		shutil.copyfile(infile, outfile)
	else:
		notFoundedWords.append(word)
		print 'not found', word


#	print word, lang


# обрабатывает строку из нескольких слов. lang = 'en'/'ru'
def processWords(words, lang):
	# если несколько слов через ;
	posW = 0
	while True:
		newPosW1 = words.find(';', posW+1)
		newPosW2 = words.find(';', posW+1)
		newPosW = newPosW1
		if newPosW2 > 0 and newPosW2 < newPosW1:
			newPosW = newPosW2;

		if newPosW < 0:
			word = words[posW:]
		else:
			word = words[posW:newPosW]
		
		word = word.strip()
			
		if len(word) > 0:
			processWord(word, lang)
			
		posW = newPosW
		if posW < 0:
			break
		posW += 1




if len(sys.argv) != 4:
	print "usage: sound-dict.py <dictionary filename> <from dir> <to dir>"
	sys.exit(1)


dictFile = sys.argv[1]
fromDir = sys.argv[2]
toDir = sys.argv[3]

notFoundedWords = []

if not os.path.exists(toDir+'-en'):
	os.makedirs(toDir+'-en')
	
if not os.path.exists(toDir+'-ru'):
	os.makedirs(toDir+'-ru')

print ': ', dictFile, fromDir, toDir

f = open(dictFile, 'rb')
for line in f:
	pos1 = line.find('  ')
	pos2 = line.find('\t')
	pos = pos2
	if (pos1 < pos2) or (pos2 < 0):
		pos1 = pos2
	engl = line[0:pos].strip()
	russ = line[pos:].strip()
	
	processWords(engl, 'en')
	processWords(russ, 'ru')
  
f.close()

if len(notFoundedWords) > 0:
	print "not found:"
for w in notFoundedWords:
	print '  ', w