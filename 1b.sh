#!/bin/bash
ADDRESS_BOOK="address_book.txt"
create_address_book() {
if [ ! -f "$ADDRESS_BOOK" ]; then
touch "$ADDRESS_BOOK"
echo "Address book created."
else
echo "Address book already exists."
fi
}
view_address_book() {
if [ -f "$ADDRESS_BOOK" ]; then
if [ -s "$ADDRESS_BOOK" ]; then
cat "$ADDRESS_BOOK"
else
echo "Address book is empty."
fi
else
echo "Address book does not exist. Please create it first."
fi
}
insert_record() {
echo "Enter Name:"
read name
echo "Enter Phone:"
read phone
echo "Enter Email:"
read email
echo "$name, $phone, $email" >> "$ADDRESS_BOOK"
echo "Record inserted."
}
delete_record() {
echo "Enter the Name of the record to delete:"
read name
if grep -q "^$name," "$ADDRESS_BOOK"; then
grep -v "^$name," "$ADDRESS_BOOK" > temp.txt && mv temp.txt "$ADDRESS_BOOK"
echo "Record deleted."
else
echo "Record not found."
fi
}
modify_record() {
echo "Enter the Name of the record to modify:"
read name
if grep -q "^$name," "$ADDRESS_BOOK"; then
grep -v "^$name," "$ADDRESS_BOOK" > temp.txt
echo "Enter new Phone:"
read phone
echo "Enter new Email:"
read email
echo "$name, $phone, $email" >> temp.txt
mv temp.txt "$ADDRESS_BOOK"
echo "Record modified."
else
echo "Record not found."
fi
}
while true; do
echo ""
echo "Address Book Menu:"
echo "a) Create address book"
echo "b) View address book"
echo "c) Insert a record"
echo "d) Delete a record"
echo "e) Modify a record"
echo "f) Exit"
echo "Enter your choice: "
read choice
case $choice in
a) create_address_book ;;
b) view_address_book ;;
c) insert_record ;;
d) delete_record ;;
e) modify_record ;;
f) echo "Exiting..."; exit 0 ;;
*) echo "Invalid choice. Please try again." ;;
esac
done
