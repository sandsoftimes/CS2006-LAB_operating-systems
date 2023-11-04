echo "Creating a nameFile: "
touch sherjeel.txt
echo "Enter Your Name: "
nano sherjeel.txt
echo "Creating a rollnoFile: "
touch rollNo.txt
echo "Enter Roll No: "
nano rollNo.txt
echo "Name and Rollno Successfully Entered: "
echo "Creating a Combining File: "
touch combYined.txt 
cat sherjeel.txt rollNo.txt > combYined.txt
echo "Creating a hello.txt file: "
touch hello.txt
echo "Enter the Hello World Code in C: "
nano hello.txt 
echo "Enter the Hello.c file: "
touch hello.c
cat hello.txt > hello.c
read x 
case $x in 
    1)
        gcc hello.c -o hello 
    ;;
    2)
        ./hello 
    ;;
    3)
        cat hello.c 
    ;;
    *)
        echo "No case available"
    ;;
esac
exit 0
