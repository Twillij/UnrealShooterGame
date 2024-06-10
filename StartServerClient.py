import os
import subprocess

# Set Unreal Engine paths
ue_dir = r"C:\Users\Will\Documents\GitHub\UnrealEngine"
rel_editor_fp = r"\Engine\Binaries\Win64\UnrealEditor.exe"
ue_fp = ue_dir + rel_editor_fp

# Set project paths
project_dir = os.path.dirname(os.path.abspath(__file__))
uproject_fn = r"\UnrealShooter.uproject"
project_fp = project_dir + uproject_fn

server_params = "-server -game -log"
server_ip = "127.0.0.1:7777"

client_params = "-game -log -WINDOWED -ResX=960 -ResY=540"

client_count = None
while client_count == None:
    try:
        user_input = int(input("Enter the number of clients (between 1-8) to start:"))
        if 1 <= user_input <= 8:
            client_count = user_input
        else:
            raise ValueError
    except ValueError:
        print("You did not enter a valid integer. Please enter a number between 1-8.")

server_command = ue_fp + " " + project_fp + " " + server_params
client_command = ue_fp + " " + project_fp + " " + server_ip + " " + client_params

print("Starting server... \n" + server_command)
subprocess.Popen(server_command)

for i in range(1, client_count + 1):
    print("Starting client %d...\n" % i + client_command)
    subprocess.Popen(client_command)

input("Enter any key to exit the program...")