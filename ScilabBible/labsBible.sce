//-----Begin Application on Scilab------------------//
clc();
disp("//---------------------Bible Application--------------------------//")
book = input("Book : ","string");
chapter = input("Chapter : ","string");
verseStart = input("Verse Start : ","string");
verseStop = input("Verse Stop : ","string");
filename = getURL("http://labs.bible.org/api/?passage="+book+"+"+chapter+":"+verseStart+"-"+verseStop+"&type=text&formatting=plain","jsonFile");
json_eg = mgetl("jsonFile");
//jsonparser = JSONParse(json_eg);
//disp(jsonparser.bookname(1)+" "+jsonparser.chapter(1)+":"+jsonparser.verse(1))
//disp(json_eg);
//taille = size(jsonparser);
//for i = 1:taille(2)
//    printf("%s\n",jsonparser.text(i))
//end
VERSION = "darby"; //Constante
//bookEnglish = strsplit(book);
//sizeWord = size(bookEnglish);
//--check version--//
versionBible = htmlRead("bible-versions.xml");
codeOfBible = xmlXPath(versionBible, "//code");
sizeOfCode = size(codeOfBible);
for i=1:sizeOfCode(2)
    if codeOfBible(i).content==VERSION then
        break
    end
    if i==sizeOfCode(2) then
        disp("Version "+VERSION+" not find")
        VERSION = "darby"; //To have derby version if VERSION is not find
    end
end
//--end check version-----//
doc = xmlRead("http://api.preachingcentral.com/bible.php?passage="+book+chapter+":"+verseStart+"-"+verseStop+"&version="+VERSION);
q = xmlXPath(doc, "//text");
taille = q.size;
for i = 1:taille
    disp(q.content(i))
end
