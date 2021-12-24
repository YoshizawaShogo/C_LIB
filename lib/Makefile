default: all

# Cプログラムのアーカイブ作成用のMakefileです

MAKEFLAGS ?= -j$(shell nproc)

INTERMEDIATE := ./build
$(shell mkdir -p $(INTERMEDIATE))

CSRCDIR := src
CSRC := $(wildcard $(addprefix $(CSRCDIR)/,*.c))
OBJS := $(CSRC:$(CSRCDIR)/%.c=$(INTERMEDIATE)/%.o)
DEPE := $(OBJS:%.o=%.d)
ARCHIVE := libmy.a

CC := gcc
CFLAGS := -O2 -MMD

# allとcleanはファイルではなくターゲットであると宣言する
.PHONY: all clean
all: $(ARCHIVE)

# アーカイブする
$(ARCHIVE): $(OBJS)
	ar r $@ $^
$(OBJS): build/%.o: $(CSRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $(filter %.c,$^) -MF $(patsubst %.o,%.d,$@)

# 中間ファイルをすべて消去する
clean:
	rm -rf $(INTERMEDIATE) $(ARCHIVE)
	
-include $(DEPE)
