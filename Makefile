default: all

# Cプログラム作成用Makefileのテンプレです

MAKEFLAGS ?= -j$(shell nproc)

INTERMEDIATE := ./build
$(shell mkdir -p $(INTERMEDIATE))

CSRCDIR := src
CSRC := $(wildcard $(addprefix $(CSRCDIR)/,*.c))
OBJS := $(CSRC:$(CSRCDIR)/%.c=$(INTERMEDIATE)/%.o)
DEPE := $(OBJS:%.o=%.d)
LIBDIR := ./lib
LDFLAGS := -L$(LIBDIR)
INCLUDE := -I$(LIBDIR)/src
LIBS := -lmy
program := $(INTERMEDIATE)/program

CC := gcc
CFLAGS := -O2 -MMD -g $(INCLUDE)

# allとcleanはファイルではなくターゲットであると宣言する
.PHONY: all clean

# 実行する
all: $(program)
run: all
	./$(program)
# コンパイルする
$(program): $(OBJS)
	$(MAKE) -C $(LIBDIR)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
$(OBJS): build/%.o: $(CSRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $(filter %.c,$^) -MF $(patsubst %.o,%.d,$@)

# 中間ファイルをすべて消去する
clean:
	$(MAKE) $@ -C $(LIBDIR)
	rm -rf $(INTERMEDIATE) $(program)
	
-include $(DEPE)

