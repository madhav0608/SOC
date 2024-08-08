import tkinter as tk
from tkinter import messagebox
from tkinter import filedialog
from tkinter import simpledialog
import subprocess
import os

def show_popup():
    popup_width = 800
    popup_height = 600
    
    # Create a Toplevel window for the popup
    popup = tk.Toplevel(root)
    popup.title("Code Canvas")
    
    # Calculate the position to center the popup on the screen
    screen_width = root.winfo_screenwidth()
    screen_height = root.winfo_screenheight()
    x = (screen_width - popup_width) // 2
    y = (screen_height - popup_height) // 2
    
    # Set the size and position of the popup window
    popup.geometry(f"{popup_width}x{popup_height}+{x}+{y}")
    
    # Create a Text widget for multiline input
    text_widget = tk.Text(popup, wrap=tk.WORD, font=("Arial", 14))
    text_widget.pack(fill=tk.BOTH, expand=True, padx=20, pady=20)
    
    # Example initial text
    initial_text = ""
    text_widget.insert(tk.END, initial_text)
    
    # Create a label to show file path
    file_label = tk.Label(popup, text="File path: ")
    file_label.pack(pady=10)
    
    # Variable to store the selected file path
    file_path = ""
    
    def save_to_file():
        nonlocal file_path
        message = text_widget.get("1.0", tk.END).strip()  # Get all text from start to end
        
        if not file_path:
            # Ask user to select a file to save the text
            file_path = filedialog.asksaveasfilename(
                defaultextension=".txt",
                filetypes=[("Text files", "*.txt"), ("All files", "*.*")],
                title="Save As"
            )
            if not file_path:
                return  # User canceled save dialog
        
        try:
            with open(file_path, "w") as file:
                file.write(message)
            file_label.config(text=f"File path: {file_path}")  # Update file path label
            # messagebox.showinfo("File Saved", f"Message saved to:\n{file_path}")
        except Exception as e:
            messagebox.showerror("Error", f"An error occurred while saving:\n{str(e)}")
    
    # Create an OK button to submit the text
    ok_button = tk.Button(popup, text="Save", command=save_to_file)
    ok_button.pack(side=tk.LEFT, padx=10, pady=10)
    
    # Function to execute search
    def execute_search():
        if not file_path:
            messagebox.showwarning("File Not Saved", "Please save the file first.")
            return
        
        search_term = simpledialog.askstring("Search", "Enter text to search:")
        if not search_term:
            return  # User canceled or entered empty search term
        
        # Path to your executable
        executable_path = "./search.out"
        
        if not os.path.exists(executable_path):
            messagebox.showerror("Executable Not Found", "Could not find search.out executable.")
            return
        
        try:
            # Execute the external executable with file_path and search_term as arguments
            result = subprocess.run([executable_path, file_path, search_term], capture_output=True, text=True)
            
            # Check if search.out returned any output
            if result.stdout.strip():
                # Process the output to highlight occurrences in the Text widget
                lines = result.stdout.strip().splitlines()
                for line in lines:
                    line_number, index = map(int, line.split())
                    start_pos = f"{line_number}.{index}"
                    end_pos = f"{start_pos}+{len(search_term)}c"
                    text_widget.tag_add("highlight", start_pos, end_pos)
                
                # Configure the tag for highlighting
                text_widget.tag_config("highlight", background="#ADD8E6")
                
                # Show success message
                # messagebox.showinfo("Search Completed", f"Found {len(lines)} occurrences of '{search_term}'")
            # else:
                # messagebox.showinfo("Search Completed", f"No occurrences of '{search_term}' found.")
        
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Error", f"An error occurred while executing search:\n{str(e)}")
    
    # Create a Search button
    search_button = tk.Button(popup, text="Search", command=execute_search)
    search_button.pack(side=tk.LEFT, padx=10, pady=10)
    
    # Focus the Text widget initially
    text_widget.focus_set()

    def clear_search():
        text_widget.tag_remove("highlight", "1.0", tk.END)  # Remove highlight tag from all text    
    clear_button = tk.Button(popup, text="Clear Search", command=clear_search)
    clear_button.pack(side=tk.LEFT, padx=10, pady=10)
# Create the main window
root = tk.Tk()
root.title("Main Window")

# Create a button to trigger the popup
popup_button = tk.Button(root, text="Click for a window", command=show_popup)
popup_button.pack(pady=20)

# Run the main event loop
root.mainloop()