import json
import requests
from secrets import spotify_user_id, onrepeat_id
from refresh import Refresh


class SaveSongs:
    def __init__(self):
        self.user_id = spotify_user_id
        self.spotify_token = ""
        self.onrepeat_id = onrepeat_id
        self.tracks = ""
        self.new_playlist_id = ""

    def find_songs(self):
        print("Finding songs in On Repeat...")
        # loop through playlist tracks, add them to list

        query = "https://api.spotify.com/v1/playlists/{}/tracks".format(onrepeat_id)

        response = requests.get(query, headers={
            "Content-Type": "application/json", "Authorization": "Bearer {}".format(self.spotify_token)
        })

        response_json = response.json()
        print(response)
        f = open("tracks.txt", "a")
        for i in response_json["items"]:
            self.tracks += (i["track"]["uri"] + ",")
        f.write(self.tracks)
        self.tracks = self.tracks[:-1]
        f.close()
        self.add_to_playlist()

    def create_playlist(self):
        print("Trying to create new playlist...")
        query = "https://api.spotify.com/v1/users/{}/playlists".format(spotify_user_id)
        request_body = json.dumps({
            "name": "Circle", "description": "hello world", "public": True
        })
        response = requests.post(query, data=request_body, headers={
            "Content-Type": "application/json", "Authorization": "Bearer {}".format(self.spotify_token)
        })

        response_json = response.json()

        return response_json["id"]

    def add_to_playlist(self):
        print("Adding songs to new playlist...")

        self.new_playlist_id = self.create_playlist()

        query = "https://api.spotify.com/v1/playlists/{}/tracks?uris={}".format(self.new_playlist_id, self.tracks)

        response = requests.post(query, headers={
            "Content-Type": "application/json", "Authorization": "Bearer {}".format(self.spotify_token)
        })

        print(response.json)

    def call_refresh(self):
        print("Refreshing token...")
        refreshCaller = Refresh()

        self.spotify_token = refreshCaller.refresh()

        self.find_songs()


a = SaveSongs()
a.call_refresh()
