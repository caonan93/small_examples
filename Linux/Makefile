TARGET += ./bin/banksort \
		  ./bin/circular_buffer \
		  ./bin/curl_test \
		  ./bin/regdex_test		  
all:$(TARGET)
./bin/%: ./%.cc
	g++ -o $(@) $(<) -g
	
./bin/curl_test: ./curl_test.cc	
	g++ -o ./bin/curl_test curl_test.cc -lcurl -g
./bin/regdex_test:./regdex_test.cc
	g++ -o $(@) $(<) -lboost_regex -g 
.PHONY:clean
clean:
	rm -rf ./bin/*
