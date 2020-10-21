./tutorial < minilibx_doc.rtf > yours_.res
cat -e yours_.res > yours.res
cat -e < minilibx_doc.rtf > original.res
diff -y --suppress-common-line original.res yours.res
rm -rf original.res yours_.res yours.res get_next_line