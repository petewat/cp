for((i=0;i<100;i++)) do
    echo "test : " $i
    ./gen > "in.txt"
    ./sol <"in.txt"> "out.txt"
    ./test <"in.txt"> "out2.txt"
    diff "out.txt" "out2.txt"||break
done
##bash b.sh (to run)