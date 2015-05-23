dataprefix="out-click-all-refine-$1-$2"
liblinearprefix="liblinear-traindata-all-refine-$1-$2"

if [ "$1" == "" -o "$2" == "" ]; then
	echo "gendata_train_predict_refine_data threshold_item_of_session threshold_item_be_click_num"
	exit
fi

echo "============================================================================================"
echo "python tools/make_liblinear_bits.py out-click-all-refine.dat out-buy-all.dat $liblinearprefix.dat"
python tools/make_liblinear_bits.py $dataprefix.dat out-buy-all.dat $liblinearprefix.dat
echo "============================================================================================"
echo "head -n 400000 $liblinearprefix.dat > $liblinearprefix-partial.dat"
echo "tail -n 80000 $liblinearprefix.dat > $liblinearprefix-valid.dat"
head -n 400000 $liblinearprefix.dat > $liblinearprefix-partial.dat
tail -n 80000 $liblinearprefix.dat > $liblinearprefix-valid.dat
echo "============================================================================================"
echo "./train $liblinearprefix-partial.dat"
./train $liblinearprefix-partial.dat
echo "============================================================================================"
echo "./predict $liblinearprefix-valid.dat $liblinearprefix-partial.dat.model res.txt"
echo "./tools/result_01_grid $liblinearprefix-valid.dat res.txt"
./predict $liblinearprefix-valid.dat $liblinearprefix-partial.dat.model res.txt
./tools/result_01_grid $liblinearprefix-valid.dat res.txt

