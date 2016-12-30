CC = g++  

CFLAGS += -std=c++11 -Wunused-result -Wall -g -O2 -fPIC -Iheaders  
BUILD_DIR = build
# BIN = Road_Get_Main Road_Compression Part1_Task1 Ride_Get_Rides Ride_Get_Proj Ride_DivideByTime Ride_Get_Astardis Position_Get_Driver_Position Part1_Task2_1 Part1_Task2_2

BIN = Part2_GetTimeData
# BIN1 = Road_Get_Main
# BIN2 = Road_Compression
# BIN3 = Part1_Task1
# BIN4 = Ride_Get_Rides
# BIN5 = Ride_Get_Proj
# BIN6 = Ride_Get_Astardis
# BIN7 = Ride_DivideByTime
# BIN8 = Position_Get_Driver_Position
# BIN9 = Part1_Task2_1
# BIN10 = Part1_Task2_2
BIN11 = Part2_GetTimeData

MYDEPS = $(BUILD_DIR)/point.o $(BUILD_DIR)/edge.o $(BUILD_DIR)/kdtree.o $(BUILD_DIR)/astar.o $(BUILD_DIR)/analyse.o $(BUILD_DIR)/initroad.o $(BUILD_DIR)/ride.o  $(BUILD_DIR)/getprojection.o 
#MYDEPS = $(BUILD_DIR)/point.o $(BUILD_DIR)/analyse.o


SRCS = $(wildcard cpps/*.cpp)  
HEDS = $(wildcard headers/*.h)  
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))  
DEPS = $(patsubst %.o, %.d, $(OBJS))

VPATH = cpps:headers

.PHONY: all
all: _PRE $(BIN)

-include $(DEPS)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

# $(BIN1): $(BUILD_DIR)/$(BIN1).o
# 	$(CC) $(CFLAGS) -o $(BIN1) $(BUILD_DIR)/$(BIN1).o 

# $(BIN2): $(BUILD_DIR)/$(BIN2).o 
# 	$(CC) $(CFLAGS) -o $(BIN2) $(BUILD_DIR)/$(BIN2).o 

# $(BIN3): $(BUILD_DIR)/$(BIN3).o $(MYDEPS)
# 	$(CC) $(CFLAGS) -o $(BIN3) $(BUILD_DIR)/$(BIN3).o $(MYDEPS)

# $(BIN4): $(BUILD_DIR)/$(BIN4).o $(MYDEPS)
# 	$(CC) $(CFLAGS) -o $(BIN4) $(BUILD_DIR)/$(BIN4).o $(MYDEPS)

# $(BIN5): $(BUILD_DIR)/$(BIN5).o $(MYDEPS)
# 	$(CC) $(CFLAGS) -o $(BIN5) $(BUILD_DIR)/$(BIN5).o $(MYDEPS)

# $(BIN6): $(BUILD_DIR)/$(BIN6).o $(MYDEPS)
# 	$(CC) $(CFLAGS) -o $(BIN6) $(BUILD_DIR)/$(BIN6).o $(MYDEPS)

# $(BIN7): $(BUILD_DIR)/$(BIN7).o $(MYDEPS)
# 	$(CC) $(CFLAGS) -o $(BIN7) $(BUILD_DIR)/$(BIN7).o $(MYDEPS)

# $(BIN8): $(BUILD_DIR)/$(BIN8).o $(MYDEPS)
# 	$(CC) $(CFLAGS) -o $(BIN8) $(BUILD_DIR)/$(BIN8).o $(MYDEPS)

# $(BIN9): $(BUILD_DIR)/$(BIN9).o $(MYDEPS)
# 	$(CC) $(CFLAGS) -o $(BIN9) $(BUILD_DIR)/$(BIN9).o $(MYDEPS)

# $(BIN10): $(BUILD_DIR)/$(BIN10).o $(MYDEPS)
# 	$(CC) $(CFLAGS) -o $(BIN10) $(BUILD_DIR)/$(BIN10).o $(MYDEPS)

$(BIN11): $(BUILD_DIR)/$(BIN11).o $(MYDEPS) $(BUILD_DIR)/Map_Matching.o
	$(CC) $(CFLAGS) -o $(BIN11) $(BUILD_DIR)/$(BIN11).o $(MYDEPS) $(BUILD_DIR)/Map_Matching.o
#$(BIN): $(OBJS)
# 	echo "skiped"



.PHONY: _PRE
_PRE:  
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:  
	rm -fr build