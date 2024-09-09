import os
import requests
import subprocess
import requests
# Configure these variables
GITHUB_TOKEN = os.getenv('GITHUB_TOKEN')
GITHUB_USERNAME = 'tejanshu9'
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


def download_gists(platform_folder):
    # Ensure the platform folder exists
    if not os.path.exists(platform_folder):
        os.makedirs(platform_folder)
    
    headers = {
        'Authorization': f'token {GITHUB_TOKEN}',
        'Accept': 'application/vnd.github.v3+json'
    }
    gists_url = 'https://api.github.com/gists/public'
    
    try:
        response = requests.get(gists_url, headers=headers)
        response.raise_for_status()
        gists = response.json()

        for gist in gists:
            gist_id = gist['id']
            gist_url = f'https://api.github.com/gists/{gist_id}'
            gist_response = requests.get(gist_url, headers=headers)
            gist_response.raise_for_status()
            gist_data = gist_response.json()
            
            for file_name, file_data in gist_data['files'].items():
                save_path = os.path.join(platform_folder, file_name)
                with open(save_path, 'w') as file:
                    file.write(file_data['content'])
                    
        print(f'Gists downloaded and saved to {platform_folder}')
    except requests.RequestException as e:
        print(f'Failed to fetch gists. Error: {e}')

# Example call
platform_folder = 'LeetCode'
download_gists(platform_folder)


def commit_and_push_changes():
    # Navigate to your local repository
    os.chdir(REPO_PATH)

    # Stage all changes
    subprocess.run(['git', 'add', '.'])

    # Commit with a message
    commit_message = 'Added new solution from Gist'
    subprocess.run(['git', 'commit', '-m', commit_message])

    # Push to the repository
    subprocess.run(['git', 'push', 'origin', 'main'])
    print("Changes pushed to GitHub repository")


if __name__ == '__main__':
    # Step 1: Choose platform folder
    platform_folder = choose_platform_folder()

    # Step 2: Download the Gist files and save to the selected platform folder
    download_gists(platform_folder)

    # Step 3: Commit and push to GitHub
    commit_and_push_changes()
