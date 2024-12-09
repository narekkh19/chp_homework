#!/bin/bash

# Function to print IPv4 and IPv6 addresses
print_ip_addresses() {
    echo "Fetching IPv4 and IPv6 addresses..."
    ip -4 addr show | grep -oP '(?<=inet\s)\d+(\.\d+){3}' | while read -r line; do
        echo "IPv4: $line"
    done
    ip -6 addr show | grep -oP '(?<=inet6\s)[\da-f:]+(?=/)' | while read -r line; do
        echo "IPv6: $line"
    done
}

# Function to perform traceroute
trace_route() {
    read -p "Enter hostname or URL for traceroute: " hostname
    traceroute "$hostname"
}

# Function to find IP of a host
get_ip_address() {
    read -p "Enter hostname or URL: " hostname
    host "$hostname" | grep "has address" | awk '{print $NF}'
}

# Function to encrypt text or file
encrypt_data() {
    read -p "Enter the text or file to encrypt: " input
    if [ -f "$input" ]; then
        gpg -c "$input"
        echo "File encrypted to $input.gpg"
    else
        echo -n "$input" | gpg -c -o encrypted_text.gpg
        echo "Text encrypted to encrypted_text.gpg"
    fi
}

# Function to decrypt text or file
decrypt_data() {
    read -p "Enter the file to decrypt: " input
    if [ -f "$input" ]; then
        gpg -d "$input"
    else
        echo "File does not exist!"
    fi
}

# Function to compress text or file
compress_data() {
    read -p "Enter the file or text to compress: " input
    if [ -f "$input" ]; then
        gzip "$input"
        echo "File compressed to $input.gz"
    else
        echo -n "$input" | gzip > compressed_text.gz
        echo "Text compressed to compressed_text.gz"
    fi
}

# Function to restore text or file
restore_data() {
    read -p "Enter the compressed file to restore: " input
    gunzip "$input"
    echo "File restored."
}

# Function to calculate file checksum
calculate_value() {
    read -p "Enter the file name: " filename
    if [ -f "$filename" ]; then
        sha256sum "$filename"
    else
        echo "File does not exist!"
    fi
}

# Menu loop
while true; do
    clear
    echo "=== MENU ==="
    echo "1. Print IPv4 and IPv6 addresses"
    echo "2. Trace the network path"
    echo "3. Get IP address of a host"
    echo "4. Encrypt a file or text"
    echo "5. Decrypt a file or text"
    echo "6. Compress a file or text"
    echo "7. Restore a file or text"
    echo "8. Calculate the value of a file"
    echo "9. Exit"
    echo "============"
    read -p "Choose an option: " choice

    case $choice in
        1) print_ip_addresses ;;
        2) trace_route ;;
        3) get_ip_address ;;
        4) encrypt_data ;;
        5) decrypt_data ;;
        6) compress_data ;;
        7) restore_data ;;
        8) calculate_value ;;
        9) echo "Goodbye!"; exit 0 ;;
        *) echo "Invalid option. Please try again." ;;
    esac
    read -p "Press Enter to continue..."
done
