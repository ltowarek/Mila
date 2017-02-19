import csv
import re
import subprocess

if __name__ == '__main__':
    cases = [
        'bbp_parallel.exe 100 0 0 0 20',
        'bbp_parallel.exe 200 0 0 0 20',
        'bbp_parallel.exe 300 0 0 0 20',
        'bbp_parallel.exe 400 0 0 0 20',
        'bbp_parallel.exe 500 0 0 0 20',
        'bbp_parallel.exe 600 0 0 0 20',
        'bbp_parallel.exe 700 0 0 0 20',
        'bbp_parallel.exe 800 0 0 0 20',
        'bbp_parallel.exe 900 0 0 0 20',
        'bbp_parallel.exe 1000 0 0 0 20',

        'bbp_parallel.exe 500 0 0 0 20',
        'bbp_parallel.exe 500 10 0 0 20',
        'bbp_parallel.exe 500 100 0 0 20',
        'bbp_parallel.exe 500 200 0 0 20',
        'bbp_parallel.exe 500 300 0 0 20',
        'bbp_parallel.exe 500 400 0 0 20',
        'bbp_parallel.exe 500 500 0 0 20',

        'bbp_sequential.exe 100 0 20',
        'bbp_sequential.exe 200 0 20',
        'bbp_sequential.exe 300 0 20',
        'bbp_sequential.exe 500 0 20',
        'bbp_sequential.exe 400 0 20',
        'bbp_sequential.exe 600 0 20',
        'bbp_sequential.exe 700 0 20',
        'bbp_sequential.exe 800 0 20',
        'bbp_sequential.exe 900 0 20',
        'bbp_sequential.exe 1000 0 20',

        'bbp_sequential.exe 500 0 20',
        'bbp_sequential.exe 500 10 20',
        'bbp_sequential.exe 500 200 20',
        'bbp_sequential.exe 500 100 20',
        'bbp_sequential.exe 500 300 20',
        'bbp_sequential.exe 500 400 20',
        'bbp_sequential.exe 500 500 20',
    ]

    results = []

    for case in cases:
        try:
            output = subprocess.check_output(case, shell=True, stderr=subprocess.STDOUT, universal_newlines=True)
        except subprocess.CalledProcessError as error:
            print('Error occurred!')
            output = error.output

        print(output)

        device_name = ''
        m = re.search(r'Device: (.*)', output, re.MULTILINE)
        if m:
            device_name = m.group(1)

        number_of_digits = 0
        m = re.search(r'Number of Digits: (.*)', output, re.MULTILINE)
        if m:
            number_of_digits = int(m.group(1))

        starting_position = 0
        m = re.search(r'Starting Position: (.*)', output, re.MULTILINE)
        if m:
            starting_position = int(m.group(1))

        mean = 0.0
        m = re.search(r'Mean: (.*)', output, re.MULTILINE)
        if m:
            mean = float(m.group(1))

        median = 0.0
        m = re.search(r'Median: (.*)', output, re.MULTILINE)
        if m:
            median = float(m.group(1))

        variance = 0.0
        m = re.search(r'Variance: (.*)', output, re.MULTILINE)
        if m:
            variance = float(m.group(1))

        standard_deviation = 0.0
        m = re.search(r'Standard Deviation: (.*)', output, re.MULTILINE)
        if m:
            standard_deviation = float(m.group(1))

        coefficient_of_variation = 0.0
        m = re.search(r'Coefficient of Variation: (.*)', output, re.MULTILINE)
        if m:
            coefficient_of_variation = float(m.group(1))

        results.append({'Nazwa urządzenia': device_name,
                        'Liczba cyfr': number_of_digits,
                        'Pozycja początkowa': starting_position,
                        'Średnia[us]': mean,
                        'Mediana[us]': median,
                        'Standardowe odchylenie[us]': standard_deviation,
                        'Kowariancja': coefficient_of_variation,
                        'CMD': case})

    with open('results_bbp.csv', 'wt', encoding='utf-8', newline='') as results_file:
        csv_writer = csv.DictWriter(results_file,
                                    ['Nazwa urządzenia', 'Liczba cyfr', 'Pozycja początkowa', 'Średnia[us]',
                                     'Mediana[us]', 'Standardowe odchylenie[us]', 'Kowariancja', 'CMD'])
        csv_writer.writeheader()
        csv_writer.writerows(results)
