//-----Begin Application on Scilab------------------//
clc();
disp("//---------------------Bible Application--------------------------//")
book = input("Book : ","string");
chapter = input("Chapter : ","string");
verseStart = input("Verse Start : ","string");
verseStop = input("Verse Stop : ","string");

VERSION = "darby"; //Constante
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

//Query to find verses
doc = xmlRead("http://api.preachingcentral.com/bible.php?passage="+book+chapter+":"+verseStart+"-"+verseStop+"&version="+VERSION);
q = xmlXPath(doc, "//text");
taille = q.size;

//Display all verses demand by user
for i = 1:taille
    disp(q.content(i))
end
//En of application
