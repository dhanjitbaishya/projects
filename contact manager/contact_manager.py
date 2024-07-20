from pymongo import MongoClient

client = MongoClient("mongodb://localhost:27017/")
db = client["contact_manager_db"]
contacts_collection = db["contacts"]

def add_contact(name, phone, email, address):
    contact = {
        "name": name,
        "phone": phone,
        "email": email,
        "address": address
    }
    contacts_collection.insert_one(contact)
    print(f"Contact {name} added successfully.")

def update_contact(name, new_phone=None, new_email=None, new_address=None):
    query = {"name": name}
    new_values = {"$set": {}}
    if new_phone:
        new_values["$set"]["phone"] = new_phone
    if new_email:
        new_values["$set"]["email"] = new_email
    if new_address:
        new_values["$set"]["address"] = new_address

    result = contacts_collection.update_one(query, new_values)
    if result.modified_count > 0:
        print(f"Contact {name} updated successfully.")
    else:
        print(f"Contact {name} not found.")

def delete_contact(name):
    query = {"name": name}
    result = contacts_collection.delete_one(query)
    if result.deleted_count > 0:
        print(f"Contact {name} deleted successfully.")
    else:
        print(f"Contact {name} not found.")

def search_contact(name=None, phone=None):
    query = {}
    if name:
        query["name"] = name
    if phone:
        query["phone"] = phone

    results = contacts_collection.find(query)
    for contact in results:
        print(contact)

def list_contacts():
    contacts = contacts_collection.find()
    for contact in contacts:
        print(contact)

def main():
    while True:
        print("\nContact Management System")
        print("1. Add Contact")
        print("2. Update Contact")
        print("3. Delete Contact")
        print("4. Search Contact")
        print("5. List Contacts")
        print("6. Exit")

        choice = input("Enter your choice: ")

        if choice == '1':
            name = input("Enter name: ")
            phone = input("Enter phone: ")
            email = input("Enter email: ")
            address = input("Enter address: ")
            add_contact(name, phone, email, address)
        elif choice == '2':
            name = input("Enter name to update: ")
            phone = input("Enter new phone (or leave blank): ")
            email = input("Enter new email (or leave blank): ")
            address = input("Enter new address (or leave blank): ")
            update_contact(name, phone if phone else None, email if email else None, address if address else None)
        elif choice == '3':
            name = input("Enter name to delete: ")
            delete_contact(name)
        elif choice == '4':
            name = input("Enter name to search (or leave blank): ")
            phone = input("Enter phone to search (or leave blank): ")
            search_contact(name if name else None, phone if phone else None)
        elif choice == '5':
            list_contacts()
        elif choice == '6':
            break
        else:
            print("Invalid choice, please try again.")

if __name__ == "__main__":
    main()

