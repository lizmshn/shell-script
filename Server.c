#!/bin/bash
# Функция для проверки существования директории перед удалением
check_directory_delete() {
local dir=$1
if [ -d "/$HOME/lab1/$dir" ]; then
echo "$(date '+%Y-%m-%d %H:%M:%S') - Directory '$dir' exists." »
log.log
echo "Directory '$dir' exists."
else
echo "$(date '+%Y-%m-%d %H:%M:%S') - Error: Directory '$dir' does not
exist." » log.log
echo "Error: Directory '$dir' does not exist."
exit 1
fi
}
# Функция для проверки существования директории перед
восстановлением
check_directory_restore() {
local dir=$1
if [ -d "/$HOME/.local/share/Trash/files/$dir" ]; then
echo "$(date '+%Y-%m-%d %H:%M:%S') - Directory '$dir' exists." »
log.log
else
echo "$(date '+%Y-%m-%d %H:%M:%S') - Error: Directory '$dir' does not
exist." » log.log
exit 1
fi
}
echo "What do you want to do with directory: delete or restore [d/r]"
echo "$(date '+%Y-%m-%d %H:%M:%S') - What do you want to do with
directory: delete or restore [d/r]" » log.log
read choice
echo "$(date '+%Y-%m-%d %H:%M:%S') - Action started" » log.log
if [ "$choice" == "d" ] || [ "$choice" == "D" ]; then
echo "$(date '+%Y-%m-%d %H:%M:%S') - Write name directory" » log.log
echo "Write name directory"
read dir
check_directory_delete "$dir"
echo "$(date '+%Y-%m-%d %H:%M:%S') - Do you really want to delete
$dir [y/n]" » log.log
echo "Do you really want to delete $dir [y/n]"
read choice_delete
if [ "$choice_delete" == "y" ] || [ "$choice_delete" == "Y" ]; then
mv /$HOME/lab1/$dir /$HOME/.local/share/Trash/files
echo "$(date '+%Y-%m-%d %H:%M:%S') - Directory $dir was successfully
deleted" » log.log
echo "Directory $dir was successfully deleted"
# Создать .trashinfo файл
echo "[Trash Info]
Path=$HOME/lab1/$dir
DeletionDate=$(date +%Y-%m-%dT%H:%M:%S)" >
$HOME/.local/share/Trash/info/$dir.trashinfo
elif [ "$choice_delete" == "n" ] || [ "$choice_delete" == "N" ]; then
echo "$(date '+%Y-%m-%d %H:%M:%S') - Exit. Directory $dir don't
delete." » log.log
echo "Exit. Directory $dir don't delete."
fi
elif [ "$choice" == "r" ] || [ "$choice" == "R" ]; then
echo "$(date '+%Y-%m-%d %H:%M:%S') - Write name directory" » log.log
echo "Write name directory"
read dir
check_directory_restore "$dir"
echo "$(date '+%Y-%m-%d %H:%M:%S') - Do you really want to restore
$dir [y/n]" » log.log
echo "Do you really want to restore $dir [y/n]"
read choice_restore
if [ "$choice_restore" == "y" ] || [ "$choice_restore" == "Y" ]; then
# Получить путь к удаленному каталогу из .trashinfo файла
trash_info_file="$HOME/.local/share/Trash/info/$dir.trashinfo"
if [ -f "$trash_info_file" ]; then
trash_path=$(grep -Po '(?<=^Path=).+' "$trash_info_file")
if [ -n "$trash_path" ]; then
mv /$HOME/.local/share/Trash/files/$dir "$trash_path"
echo "$(date '+%Y-%m-%d %H:%M:%S') - Directory $dir was successfully
restored to $trash_path" » log.log
echo "Directory $dir was successfully restored to $trash_path"
rm /$HOME/.local/share/Trash/info/$dir.trashinfo
else
echo "$(date '+%Y-%m-%d %H:%M:%S') - Error: Path not found in
.trashinfo file." » log.log
echo "Error: Path not found in .trashinfo file."
fi
else
echo "$(date '+%Y-%m-%d %H:%M:%S') - Error: .trashinfo file not found."
» log.log
echo "Error: .trashinfo file not found."
fi
elif [ "$choice_restore" == "n" ] || [ "$choice_restore" == "N" ]; then
echo "$(date '+%Y-%m-%d %H:%M:%S') - Exit. Directory $dir don't
restore." » log.log
echo "Exit. Directory $dir don't restore."
fi
fi
echo "$(date '+%Y-%m-%d %H:%M:%S') - Action completed" » log.log
