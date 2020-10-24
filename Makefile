SOURCE_DIR      = src
INCLUDE_DIR     = include
OBJECT_DIR      = obj
DEMO_SOURCE_DIR = demo
DEMO_OBJECT_DIR = $(OBJECT_DIR)/demo
BUILD_DIR       = build

CC       = cc
CFLAGS   = -Wall -Werror -Wpedantic -ansi -I$(INCLUDE_DIR) -D_POSIX_C_SOURCE=199309L #TODO: remove this feature test macro
LIBS     = x11
LDFLAGS  = $(shell pkg-config --cflags --libs $(LIBS))

DEBUGGER = gdb

OBJECT_DIR_STAMP      = $(OBJECT_DIR)/.dirstamp \
                        $(OBJECT_DIR)/backends/x11/.dirstamp
DEMO_OBJECT_DIR_STAMP = $(DEMO_OBJECT_DIR)/.dirstamp
BUILD_DIR_STAMP       = $(BUILD_DIR)/.dirstamp

TARGET_STATIC = $(BUILD_DIR)/libgosh.a
TARGET_SHARED = $(BUILD_DIR)/libgosh.so
TARGET_DEMO   = $(BUILD_DIR)/gosh_demo

SOURCES        = $(wildcard $(SOURCE_DIR)/*.c $(SOURCE_DIR)/backends/*/*.c)
DEMO_SOURCES   = $(wildcard $(DEMO_SOURCE_DIR)/*.c)
OBJECTS_STATIC = $(patsubst $(SOURCE_DIR)/%.c,$(OBJECT_DIR)/%_static.o,$(SOURCES))
OBJECTS_SHARED = $(patsubst $(SOURCE_DIR)/%.c,$(OBJECT_DIR)/%_shared.o,$(SOURCES))
OBJECTS_DEMO   = $(patsubst $(DEMO_SOURCE_DIR)/%.c,$(DEMO_OBJECT_DIR)/%.o,$(DEMO_SOURCES))

DEPENDENCIES_STATIC = $(OBJECTS_STATIC:%.o=%.d)
DEPENDENCIES_SHARED = $(OBJECTS_SHARED:%.o=%.d)
DEPENDENCIES_DEMO   = $(OBJECTS_DEMO:%.o=%.d)

ifeq ($(PREFIX),)
    PREFIX = /usr
endif
INSTALL_PREFIX = $(DESTDIR)$(PREFIX)

.PHONY: all
all: release

.PHONY: release
release: CFLAGS += -O3
release: $(TARGET_DEMO) static shared

.PHONY: debug
debug: CFLAGS += -Og -g -DDEBUG
debug: demo
	$(DEBUGGER) -ex run --arg $(TARGET_DEMO)

.PHONY: static
static: $(TARGET_STATIC)

.PHONY: shared
shared: $(TARGET_SHARED)

.PHONY: demo
demo: $(TARGET_DEMO)

%.a: $(BUILD_DIR_STAMP) $(OBJECTS_STATIC)
	ar rcs $@ $(filter-out $<,$^)

%.so: $(BUILD_DIR_STAMP) $(OBJECTS_SHARED)
	$(CC) $(CFLAGS) -shared -o $@ $(filter-out $<,$^) $(LDFLAGS)

$(TARGET_DEMO): $(BUILD_DIR_STAMP) $(OBJECTS_STATIC) $(OBJECTS_DEMO)
	$(CC) $(CFLAGS) -o $@ $(filter-out $<,$^) $(LDFLAGS)

$(OBJECTS_STATIC): $(OBJECT_DIR)/%_static.o: $(SOURCE_DIR)/%.c $(OBJECT_DIR_STAMP) $(DEPENDENCIES)
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

$(OBJECTS_SHARED): $(OBJECT_DIR)/%_shared.o: $(SOURCE_DIR)/%.c $(OBJECT_DIR_STAMP) $(DEPENDENCIES)
	$(CC) $(CFLAGS) -MMD -fPIC -c -o $@ $<

$(OBJECTS_DEMO): $(DEMO_OBJECT_DIR)/%.o: $(DEMO_SOURCE_DIR)/%.c $(DEMO_OBJECT_DIR_STAMP) $(DEPENDENCIES)
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

-include $(DEPENDENCIES_STATIC)
-include $(DEPENDENCIES_SHARED)
-include $(DEPENDENCIES_DEMO)

.PRECIOUS: %/.dirstamp
%/.dirstamp:
	mkdir -p $(@D)
	touch $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(OBJECT_DIR)

.PHONY: install
install:
	install -d $(INSTALL_PREFIX)/include/
	install -d $(INSTALL_PREFIX)/lib/
	install -d $(INSTALL_PREFIX)/bin/
	install -m 644 $(INCLUDE_DIR)/* $(INSTALL_PREFIX)/include/
	install -m 644 $(TARGET_STATIC) $(TARGET_SHARED) $(INSTALL_PREFIX)/lib/
	install -m 644 $(TARGET_DEMO) $(INSTALL_PREFIX)/bin/
