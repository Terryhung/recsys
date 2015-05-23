dataprefix="out-click-all-refine-$1-$2"
liblinearprefix="liblinear-traindata-all-refine-$1-$2"

if [ "$1" == "" -o "$2" == "" ]; then
	echo "gendata_train_predict_refine_data threshold_item_of_session threshold_item_be_click_num"
	exit
fi

set -v

./tools/data_refiner out-click-all.dat $dataprefix.dat $1 $2 
python tools/make_liblinear_bits.py $dataprefix.dat out-buy-all.dat $liblinearprefix.dat
tools/make_partial_valid_data $liblinearprefix.dat
./train $liblinearprefix-partial.dat
./predict $liblinearprefix-valid.dat $liblinearprefix-partial.dat.model res.txt
./tools/result_01_grid $liblinearprefix-valid.dat res.txt

