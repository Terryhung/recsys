CPP_FLAGS = 
EXECUTABLE = tools/data_refiner tools/bindata_reader tools/result_01_grid tools/weight_file_generator tools/data_analysis tools/textdata_compressor tools/make_partial_valid_data


all: $(EXECUTABLE)

%: %.cpp
	g++ $(CPP_FLAGS) $< -o $@
	
