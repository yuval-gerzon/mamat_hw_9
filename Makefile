
LIB_SRCS = string.cpp field.cpp ip.cpp port.cpp
APP_SRCS = main.cpp
COMP = g++  # C++
COMP_FLAGS = -Wall -Wextra -L. -g
LDFLAGS = -fPIC -shared
RM = rm -f

DEST_LIB = firewall
DEST_APP = firewall.exe
OTHER_LIB = input

all:${DEST_APP}

$(DEST_LIB):
	$(COMP) ${COMP_FLAGS} ${LDFLAGS} ${LIB_SRCS} -o lib${DEST_LIB}.so

${DEST_APP}: ${DEST_LIB} 
	$(COMP) ${COMP_FLAGS} ${APP_SRCS} -o ${DEST_APP} -l$(DEST_LIB) -l$(OTHER_LIB)
	
clean:
	-${RM} ${DEST_LIB} ${DEST_APP}