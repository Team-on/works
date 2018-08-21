OIFS="$IFS"
IFS=$'\n'
for i in $(find `pwd` -name "*.txt"); 
do 
    mv "$i" "${i%.txt}.cpp"
done
IFS="$OIFS"