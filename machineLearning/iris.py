from sklearn import datasets

dataset = datasets.load_iris()

#print('name : \n{}'.format(dataset['feature_names']))

#print('input data:\n{}'.format(dataset['data'][:5]),format(dataset['target_names']))

#print('target:\n{}'.format(dataset['target_names']),'\n'+format(dataset['target']))

print('feature_names\n{}'.format(dataset['feature_names']))
print('data\n{}'.format(dataset['data'][:5]))
print('target_names\n{}'.format(dataset['target_names']))
print('target\n{}'.format(dataset['target']))


