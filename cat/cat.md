# more、less、cat、tail、head、hexdump #

- ## more ##
more 命令用于逐页显示文本文件的内容。当你打开一个大型文本文件时，使用 more 命令可以一次只显示一页，以便你逐页查看文件内容。使用空格键来翻页，按 "q" 键退出 more。

- ## less ##
与 more 类似，less 命令也用于分页查看文本文件，但它提供了更多的功能和交互性。你可以使用 less 来向前和向后滚动，搜索特定文本，类似man手册那样，输入/查找指定的内容。退出 less 也是通过按 "q" 键。

- ## cat ##
cat 命令是“concatenate”的缩写，它的主要作用是将一个或多个文本文件的内容连接在一起并将结果输出到终端。例如，你可以使用 cat 命令将多个文件的内容合并到一个新文件中。

- ## head ##
head 命令用于查看文件的开头部分，默认情况下它会显示文件的前10行内容。同样，你可以使用 -n 选项来指定要显示的行数，例如 head -n 15 filename 将显示文件的前15行。

- ## tail ##
tail 命令用于查看文件的末尾部分，默认情况下它会显示文件的最后10行内容。这在实时查看日志文件或监视文件变化时非常有用。使用 -n 选项来指定显示的行数，例如 tail -n 20 filename 将显示文件的最后20行。-f 选项用于跟踪文件变化，例如 tail -f filename 将跟踪文件的变化并显示最新的内容。

- ## hexdump ##
hexdump 是一个用于查看和分析二进制文件的命令行工具。它以十六进制和ASCII字符的形式显示文件的内容，使你能够深入了解文件的结构和内容.
-C：以十六进制和ASCII字符的形式同时显示文件内容。
-n：指定要显示的字节数。
-s：跳过文件的前几个字节，然后开始显示。
-v：详细输出，显示文件的偏移量。
-e：自定义输出格式，允许你指定如何显示数据。