echo "Script For The Function Call"
sum(){
    x=$1
    y=$2
    k=0
    k=$(($x+$y))
    return $k
}

sum 0 0
echo "Value Got It Is:$?"
exit 0