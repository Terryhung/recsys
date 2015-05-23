CPP_FLAGS = 
EXECUTABLE = tools/data_refiner tools/bindata_reader tools/result_01_grid tools/weight_file_generator tools/data_analysis tools/textdata_compressor


all: $(EXECUTABLE)

%: %.cpp
	g++ $(CPP_FLAGS) $< -o $@
	
