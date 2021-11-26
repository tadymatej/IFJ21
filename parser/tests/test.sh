#../make
#sudo apt install luarocks
#sudo apt update luarocks
# git clone https://github.com/teal-language/tl
#
#❯ sudo luarocks install tl
#Installing https://luarocks.org/tl-0.13.2-1.src.rock
#Error: Rockspec format 3.0 is not supported, please upgrade LuaRocks.

GREEN="\e[32m"
RED="\e[31m"
NORMAL="\e[39m"

echo "$GREEN#########################################################################################" ;
echo "# *.tl Testing " ;
echo "#########################################################################################$NORMAL" ;
for f in *.tl; do
    echo "$f ***************************" ;
    head -1 $f;
    cat $f | ../parser > $f.txt
    diff $f.txt $f.prg
done

echo "#" ;
echo "#" ;
echo "$RED#########################################################################################" ;
echo "# *.tl-err Errror Testing $RED" ;
echo "#########################################################################################$NORMAL" ;
for f in *.tl-err; do
    echo "$f ***************************" ;
    head -1 $f;
    cat $f | ../parser > $f.txt
done

#for f in *.tl; do
echo "# Dodelat str. 13 tl run $f.prg < $f.in > $f.out " ;
echo "# Dodelat str. 13 ic2lint run $f.prg < $f.in > $f.out " ;
#done
