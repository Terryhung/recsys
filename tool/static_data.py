import csv


def open_file(filename):
    with open(filename, 'r') as f:
        reader = list(csv.reader(f))
        print ('--------load_finish')
        return reader


def get_category(data):
    good_category = set(map(lambda x: [x[-2], x[-1]], data))
    print good_category


if __name__ == "__main__":
    data = open_file('../data/clicksaa')
