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
BLUE="\e[36m"
PURPLE="\e[35;1m"
NORMAL="\e[39m"


echo "$BLUE@NOTE:$NORMAL All test files .tl or .tl-err must have$PURPLE LF$NORMAL EOF sequence!!!!!";

echo ""
echo ""

echo "$GREEN#########################################################################################" ;
echo "# *.tl Testing " ;
echo "#########################################################################################$NORMAL" ;
for f in *.tl; do
    echo "----------------------------- $f -------------------------------" ;
    head -1 $f;
    #cat $f | ../parser > .code/$f.code
    cat $f | ../parser > .prg/$f.txt

    # pro testovani po uprave PSA
    #cat $f | ../parser  > .vzor/$f.txt

    case $? in
        0)
            echo "$GREEN OK $NORMAL [0]";
            ;;
        1)
            echo "$RED ERR $NORMAL [1]";
            ;;
        2)
            echo "$RED ERR $NORMAL [2]";
            ;;
        3)
            echo "$RED ERR $NORMAL [3]";
            ;;
        4)
            echo "$RED ERR $NORMAL [4]";
            ;;
        5)
            echo "$RED ERR $NORMAL [5]";
            ;;
        6)
            echo "$RED ERR $NORMAL [6]";
            ;;
        7)
            echo "$RED ERR $NORMAL [7]";
            ;;
        8)
            echo "$RED ERR $NORMAL [8]";
            ;;
        9)
            echo "$RED ERR $NORMAL [9]";
            ;;
        99)
            echo "$BLUE ERR $NORMAL [99]";
            ;;
    esac

    #diff .vzor/$f.txt .vzor/$f.vzor > $f.diff

    diff .prg/$f.txt .prg/$f.prg
    #tail -1 .prg/$f.txt;
    echo "";
done
echo ""
echo ""
echo "$RED#########################################################################################" ;
echo "# *.tl-err ERROR Testing $RED" ;
echo "#########################################################################################$NORMAL" ;
for f in *.tl-err; do
    echo "----------------------------- $f -------------------------------" ;
    head -1 $f;
    #cat $f | ../parser > .code/$f.code
    cat $f | ../parser > .prg/$f.txt

    # pro testovani po uprave PSA
    #cat $f | ../parser > .vzor/$f.txt

    case $? in
        0)
            echo "$GREEN OK $NORMAL [0]";
            ;;
        1)
            echo "$RED ERR $NORMAL [1]";
            ;;
        2)
            echo "$RED ERR $NORMAL [2]";
            ;;
        3)
            echo "$RED ERR $NORMAL [3]";
            ;;
        4)
            echo "$RED ERR $NORMAL [4]";
            ;;
        5)
            echo "$RED ERR $NORMAL [5]";
            ;;
        6)
            echo "$RED ERR $NORMAL [6]";
            ;;
        7)
            echo "$RED ERR $NORMAL [7]";
            ;;
        8)
            echo "$RED ERR $NORMAL [8]";
            ;;
        9)
            echo "$RED ERR $NORMAL [9]";
            ;;
        99)
            echo "$BLUE ERR $NORMAL [99]";
            ;;
    esac

    #diff .vzor/$f.txt .vzor/$f.vzor > $f.diff

    diff .prg/$f.txt .prg/$f.prg

done
echo ""
echo ""
echo "$BLUE@NOTE:$NORMAL All test files .tl or .tl-err must have$PURPLE LF$NORMAL EOF sequence!!!!!";
#for f in *.tl; do
echo "# Dodelat str. 13 tl run $f.prg < $f.in > $f.out " ;
echo "# Dodelat str. 13 ic2lint run $f.prg < $f.in > $f.out " ;
#done

# remove .txt files
rm -f *.txt
