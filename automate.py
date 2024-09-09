import os
import requests
import subprocess

# Configure these variables
GITHUB_TOKEN = os.getenv('GITHUB_TOKEN')  # Make sure your environment variable is set
GITHUB_USERNAME = 'tejanshu9'  # Replace with your GitHub username
REPO_PATH = '/home/tejanshu/Coding-Solutions-Repository'  # Local path to the GitHub repository

# Platform folders
PLATFORM_FOLDERS = {
    1: 'LeetCode',
    2: 'GeeksforGeeks',
    3: 'Neetcode',
    4: 'InterviewBit',
    5: 'Others'
}

# Gist API URL
GIST_API_URL = f'https://api.github.com/users/{GITHUB_USERNAME}/gists'


def choose_platform_folder():
    print("Choose the platform folder to save the Gist:")
    for key, value in PLATFORM_FOLDERS.items():
        print(f"{key}. {value}")

    choice = int(input("Enter your choice (1-5): "))
    return PLATFORM_FOLDERS.get(choice, 'Others')  # Default to 'Others' if invalid


def create_folder_with_question_number(platform_folder):
    question_number = input("Enter the question number (or type 'n' if no number): ").strip()
    
    if question_number.lower() == 'n':
        question_name = input("Enter the question name: ").strip()
        folder_name = question_name
    else:
        folder_name = question_number

    save_path = os.path.join(REPO_PATH, platform_folder, folder_name)
    os.makedirs(save_path, exist_ok=True)
    return save_path


def save_solution_to_folder(save_path):
    file_name = input("Enter the solution file name (e.g., solution.cpp): ").strip()
    solution_content = input("Paste the solution content: ")

    file_path = os.path.join(save_path, file_name)
    with open(file_path, 'w') as file:
        file.write(solution_content)
    print(f"Solution saved to: {file_path}")


def commit_and_push_changes():
    # Navigate to your local repository
    os.chdir(REPO_PATH)

    # Stage all changes
    subprocess.run(['git', 'add', '.'], check=True)

    # Commit with a message
    commit_message = 'Added new solution'
    subprocess.run(['git', 'commit', '-m', commit_message], check=True)

    # Push to the repository
    subprocess.run(['git', 'push', 'origin', 'main'], check=True)
    print("Changes pushed to GitHub repository")


if __name__ == '__main__':
    # Step 1: Choose platform folder
    platform_folder = choose_platform_folder()

    # Step 2: Create a folder with question number or name
    save_path = create_folder_with_question_number(platform_folder)

    # Step 3: Save the solution to the created folder
    save_solution_to_folder(save_path)

    # Step 4: Commit and push to GitHub
    commit_and_push_changes()
