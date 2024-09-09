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


def download_gists(destination_folder):
    headers = {'Authorization': f'token {GITHUB_TOKEN}'}
    response = requests.get(GIST_API_URL, headers=headers)

    if response.status_code != 200:
        print(f"Failed to fetch gists. Status Code: {response.status_code}")
        return

    gists = response.json()

    for gist in gists:
        gist_id = gist['id']
        files = gist['files']

        for file_name, file_info in files.items():
            file_url = file_info['raw_url']

            # Download the file content
            file_response = requests.get(file_url)
            if file_response.status_code == 200:
                # Save the file in the specific platform folder
                save_path = os.path.join(REPO_PATH, destination_folder, file_name)
                os.makedirs(os.path.dirname(save_path), exist_ok=True)
                with open(save_path, 'w') as file:
                    file.write(file_response.text)
                print(f"Downloaded: {file_name} from Gist ID: {gist_id} to {destination_folder}")
            else:
                print(f"Failed to download {file_name}")


def commit_and_push_changes():
    # Navigate to your local repository
    os.chdir(REPO_PATH)

    # Stage all changes
    subprocess.run(['git', 'add', '.'], check=True)

    # Commit with a message
    commit_message = 'Added new solution from Gist'
    subprocess.run(['git', 'commit', '-m', commit_message], check=True)

    # Push to the repository
    subprocess.run(['git', 'push', 'origin', 'main'], check=True)
    print("Changes pushed to GitHub repository")


if __name__ == '__main__':
    # Step 1: Choose platform folder
    platform_folder = choose_platform_folder()

    # Step 2: Download the Gist files and save to the selected platform folder
    download_gists(platform_folder)

    # Step 3: Commit and push to GitHub
    commit_and_push_changes()
