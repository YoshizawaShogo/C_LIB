default: all

# Cプログラム作成用Makefileのテンプレです

INTERMEDIATE := ./build
$(shell mkdir -p $(INTERMEDIATE))

CSRCDIR := src
CSRC := $(wildcard $(addprefix $(CSRCDIR)/,*.c))
OBJS := $(addprefix $(INTERMEDIATE)/,$(notdir $(CSRC:%.c=%.o)))
DEPE := $(addprefix $(INTERMEDIATE)/,$(notdir $(CSRC:%.c=%.d)))
LIBDIR := ./lib
LDFLAGS := -L$(LIBDIR)
INCLUDE := -I$(LIBDIR)/src
LIBS := -lmy
program := program

CC := gcc
CFLAGS := -O2 -MMD -g $(INCLUDE) # $(addprefix -I,$(INCLUDE_PATH))

# allとcleanはファイルではなくターゲットであると宣言する
.PHONY: all clean

# 実行する
all: $(program)
	./$<
# コンパイルする
$(program): $(OBJS)
	make -C $(LIBDIR)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
$(OBJS): build/%.o: $(CSRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $(filter %.c,$^) -MF $(patsubst %.o,%.d,$@)

# 中間ファイルをすべて消去する
clean:
	make $@ -C $(LIBDIR) 
	rm -rf $(INTERMEDIATE) $(program)
	
-include $(DEPE)

