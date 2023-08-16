import argparse
import json
import datetime

# Banner
BANNER = """
   ______     ______     ______     ______     ______     ______     ______     ______     ______  
  /\  == \   /\  __ \   /\  ___\   /\  __ \   /\  == \   /\  ___\   /\  == \   /\  ___\   /\__  _\ 
  \ \  __<   \ \  __ \  \ \ \____  \ \  __ \  \ \  __<   \ \ \____  \ \  __<   \ \  __\   \/_/\ \/ 
   \ \_\ \_\  \ \_\ \_\  \ \_____\  \ \_\ \_\  \ \_____\  \ \_____\  \ \_\ \_\  \ \_____\    \ \_\ 
    \/_/ /_/   \/_/\/_/   \/_____/   \/_/\/_/   \/_____/   \/_____/   \/_/ /_/   \/_____/     \/_/ 
                                                                                                   

"""

def main():
    parser = argparse.ArgumentParser(description='Add extensions to user input')
    parser.add_argument('-e', '--extension_file', help='Path to text file containing extensions', required=True)
    parser.add_argument('-l', '--input_list_file', help='Path to file containing a list of entries')
    parser.add_argument('-i', '--input_file_name', help='Single file entry')
    parser.add_argument('-d', '--date', help='Year for date-based entries')
    parser.add_argument('-n', '--number_range', type=int, help='Number for range-based entries')
    parser.add_argument('-ns', '--number_separator', help='Separator for attaching numbers')
    parser.add_argument('-ds', '--date_separator', help='Separator for attaching date')
    parser.add_argument('-df', '--date_format', choices=['year', 'ymd'], help='Output format for date-based entries')
    parser.add_argument('-silent', action='store_true', help='Run the program silently without the banner')
    args = parser.parse_args()

    if not args.silent:
        print(BANNER)

    # Read extensions from text file
    try:
        with open(args.extension_file, 'r') as extension_file:
            extensions = extension_file.read().strip().split('\n')
    except FileNotFoundError:
        print("Extension file not found.")
        return

    # Prepare user inputs
    user_inputs = []
    if args.input_list_file:
        try:
            with open(args.input_list_file, 'r') as input_list_file:
                user_inputs = input_list_file.read().strip().split('\n')
        except FileNotFoundError:
            print("Input list file not found.")
            return
    if args.input_file_name:
        user_inputs.append(args.input_file_name)

    # Add extensions to user input
    outputs = []
    if args.date:
        year = int(args.date)
        for month in range(1, 13):
            for day in range(1, 32):
                try:
                    date_obj = datetime.date(year, month, day)
                    if args.date_format == 'year':
                        formatted_date = date_obj.strftime("%Y")
                    else:
                        if args.date_separator:
                            formatted_date = date_obj.strftime("%Y{}%m{}%d".format(args.date_separator, args.date_separator))
                        else:
                            formatted_date = date_obj.strftime("%Y%m%d")
                    outputs.extend([f"{user_input}-{formatted_date}.{extension}" for user_input in user_inputs for extension in extensions])
                except ValueError:
                    pass  # Ignore invalid dates
    elif args.number_range:
        separator = args.number_separator if args.number_separator else ''
        for num in range(1, args.number_range + 1):
            outputs.extend([f"{user_input}{separator}{num}.{extension}" for user_input in user_inputs for extension in extensions])
    else:
        outputs.extend([f"{user_input}.{extension}" for user_input in user_inputs for extension in extensions])

    # Print the outputs
    for output in outputs:
        print(output)

if __name__ == '__main__':
    main()
