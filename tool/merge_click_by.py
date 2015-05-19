import csv


def open_file(filename):
    with open(filename, 'r') as f:
        reader = list(csv.reader(f))
        return reader


def get_user_item(data):
    user_time_name = map(lambda x: [x[0], x[1][:10], x[2]], data)
    print user_time_name


if __name__ == "__main__":
    data = open_file('../data/yoochoose-buys.dat')
    get_user_item(data)
