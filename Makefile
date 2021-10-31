default: all

# Cプログラム作成用Makefileのテンプレです

INTERMEDIATE := ./build
$(shell mkdir -p $(INTERMEDIATE))

CSRCDIR := src
CSRC := $(wildcard $(addprefix $(CSRCDIR)/,*.c))
OBJS := $(addprefix $(INTERMEDIATE)/,$(notdir $(CSRC:%.c=%.o)))
DEPE := $(addprefix $(INTERMEDIATE)/,$(notdir $(CSRC:%.c=%.d)))

CC := gcc
INCLUDE_PATH := src
CFLAGS := -O2 -MMD # $(addprefix -I,$(INCLUDE_PATH))
test:
	@echo $(RUN)a
program := program

# allとcleanはファイルではなくターゲットであると宣言する
.PHONY: all clean

# 実行する
all: $(program)
	./$<
# コンパイルする
$(program): $(OBJS)
	$(CC) -o $@ $^
$(OBJS): build/%.o: $(CSRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ -MF $(patsubst %.o,%.d,$@)

# 中間ファイルをすべて消去する
clean:
	rm -rf $(INTERMEDIATE) $(program)
	
-include $(DEPE)

