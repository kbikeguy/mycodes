import unittest
from socialnetwork import SocialNetwork


class TestSocialNetwork(unittest.TestCase):
    def test_dfs(self):
        dictionary = {
            0: [4],
            1: [2, 5],
            2: [1],
            3: [5, 7],
            4: [0, 7],
            5: [1, 3, 6],
            6: [5, 7],
            7: [3, 4, 6]
        }

        network = SocialNetwork(dictionary)

        path = network.dfs(5)
        self.assertEqual(path, [5, 1, 2, 3, 7, 4, 0, 6])

        path = network.dfs(4)
        self.assertEqual(path, [4, 0, 7, 3, 5, 1, 2, 6])

        path = network.dfs(3)
        self.assertEqual(path, [3, 5, 1, 2, 6, 7, 4, 0])

    def test_scc(self):
        dictionary = {
            'Oscar': ['Josie'],
            'Julien': ['Oscar', 'Kaylen'],
            'Josie': ['Julien', 'Kaylen'],
            'Kaylen': ['Oscar'],
            'Jaida': ['Kaylen']
        }

        network = SocialNetwork(dictionary)
        components = network.connected_components(show_plot=False)
        self.assertEqual(components, [['Julien', 'Kaylen', 'Josie', 'Oscar'], ['Jaida']])


if __name__ == "__main__":
    unittest.main()
