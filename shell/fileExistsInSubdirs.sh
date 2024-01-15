FILE=msr.log
found=1
for D in *; do
    if [ -d "${D}" ]; then
        if [ -f "${D}/${FILE}" ]; then
            found=found+1
        else
            echo ${D}    
        fi
    fi
done
