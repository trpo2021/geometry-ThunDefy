APP = geometry
LIB = libgeometry
LDLIBS =


CPPFLAGS_TEST = -I thirdparty -I src -MP -MMD
CFLAGS = -Wall -Wextra
CPPFLAGS = -I src -MP -MMD
LDFLAGS =

APP_PATH = bin/geometry
LIB_PATH = obj/src/libgeometry/libgeometry.a

APP_PATH_TEST = bin/test

APP_SOURCES_TEST = $(shell find tests -name '*.c')
APP_OBJECTS_TEST = $(APP_SOURCES_TEST:tests/%.c=obj/test/%.o)

APP_OBJECTS = $(APP_SOURCES:src/%.c=obj/src/%.o)
APP_SOURCES = $(shell find src/geometry -name '*.c')

LIB_SOURCES = $(shell find src/libgeometry -name '*.c')
LIB_OBJECTS = $(LIB_SOURCES:src/%.c=obj/src/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)
DEPS_TEST = $(APP_OBJECTS_TEST:.o=.d) $(LIB_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS) -lm

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

obj/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


.PHONY: clean
clean:
	RM $(APP_PATH) $(LIB_PATH)
	find obj -name '*.o' -exec RM '{}' \;
	find obj -name '*.d' -exec RM '{}' \;
	
.PHONY: test
test: $(APP_PATH_TEST)

-include $(DEPS_TEST)

$(APP_PATH_TEST): $(APP_OBJECTS_TEST) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS_TEST) $^ -o $@ $(LDFLAGS) $(LDLIBS) -lm

obj/test/%.o: tests/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS_TEST) $< -o $@ $(LDLIBS)	
