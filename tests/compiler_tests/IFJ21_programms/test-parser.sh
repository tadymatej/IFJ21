##
# @file test-parser.sh 
#
# @brief Testovací skript pro syntaktickou analýzu
#
#

GREEN="\e[32m"
RED="\e[31m"
BLUE="\e[36m"
PURPLE="\e[35;1m"
NORMAL="\e[39m"

echo "$BLUE@NOTE:$NORMAL All test files .tl or .tl-err must have$PURPLE LF$NORMAL EOF sequence!!!!!";

#for i in seq {0..30}
#do
#	touch "semantic/semantic-err$i.tl"
#done


echo ""
echo ""

echo "$BLUE#########################################################################################" ;
echo "# *.tl Testing Syntax analysis" ;
echo "#########################################################################################$NORMAL" ;
for f in syntax/*.tl; do
    echo "----------------------------- $f -------------------------------" ;
    head -1 $f;
    cat $f | ./parser_test  > $f.txt
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
    
    #diff $f.txt $f.prg
    #tail -1 $f.txt;
    echo "";
done

# remove .txt files
rm -f syntax/*.txt
