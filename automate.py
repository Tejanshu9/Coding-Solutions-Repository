import os
import requests
import subprocess

# Configure these variables
GITHUB_TOKEN = os.getenv('GITHUB_TOKEN')
if not GITHUB_TOKEN:
    raise ValueError("GITHUB_TOKEN environment variable is not set")  # Make sure your environment variable is set
GITHUB_USERNAME = 'Tejanshu9'  # Replace with your GitHub username
REPO_PATH = '/home/tejanshu/Coding-Solutions-Repository'  # Local path to the GitHub repository

# Platform folders
PLATFORM_FOLDERS = {
    1: 'LeetCode',
    2: 'GeeksforGeeks',
    3: 'Neetcode',
    4: 'InterviewBit',
    5: 'LintCode'
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

    # Create the directory structure
    save_path = os.path.join(REPO_PATH, platform_folder, folder_name)
    os.makedirs(save_path, exist_ok=True)
    return save_path


def download_solution_from_gist(file_name, save_path):
    headers = {'Authorization': f'token {GITHUB_TOKEN}'}
    response = requests.get(GIST_API_URL, headers=headers)

    if response.status_code != 200:
        print(f"Failed to fetch gists. Status Code: {response.status_code}")
        print(f"Response Content: {response.text}")
        return

    gists = response.json()

    for gist in gists:
        files = gist['files']
        if file_name in files:
            file_info = files[file_name]
            file_url = file_info['raw_url']

            # Download the file content
            file_response = requests.get(file_url, headers=headers)
            if file_response.status_code == 200:
                file_path = os.path.join(save_path, file_name)
                with open(file_path, 'w') as file:
                    file.write(file_response.text)
                print(f"Downloaded: {file_name} to {save_path}")
            else:
                print(f"Failed to download {file_name}. Status Code: {file_response.status_code}")
            return

    print(f"File {file_name} not found in any Gist")

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

    # Step 3: Download the solution file from Gist and save it to the created folder
    file_name = input("Enter the solution file name (e.g., TwoSum.cpp): ").strip()
    download_solution_from_gist(file_name, save_path)

    # Step 4: Commit and push to GitHub
    commit_and_push_changes()

