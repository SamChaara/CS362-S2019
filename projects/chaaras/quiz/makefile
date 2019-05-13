#####################################################################
# Author: Sam Chaara
# Date: 5/12/2019
#####################################################################

AUTH_FIRST = Sam
AUTH_LAST = Chaara
ASSN = RandomTestingQuiz

CXX = gcc
CXXFLAGS =

OBJS = testme.o

SRCS = testme.c

HEADERS =

PROJNAME = testme

#target: dependencies
#	rules
#

${PROJNAME}: ${OBJS}
	${CXX} ${OBJS} -o ${PROJNAME} --coverage
	testme

${OBJS}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.c) --coverage

#Remove executable and object files
clean:
	rm -f ${PROJNAME} ${OBJS} $(OBJS:.o=.c.gcov) $(OBJS:.o=.gcda) $(OBJS:.o=.gcno)

#Zip function
zip:
	zip -D ${ASSN}_${AUTH_LAST}_${AUTH_FIRST}.zip ${SRCS} ${HEADERS} makefile
