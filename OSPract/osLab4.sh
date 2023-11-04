echo "for Loop"
printf "Enter the number u want to enter: "
read x
y=1
k=0
echo "The Multiplication Result is: "
for((y=1; y<=10; y++))  
do
k=$(($x * $y))
echo "$x x $y = $k"
done 
exit 0