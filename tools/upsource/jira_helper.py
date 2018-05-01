import json
import os
   
up_ip = "http://18.188.47.171:8080"

json_input = "upsource.json"
discs = {}
acc = []
rej = []
style = []


def get_url(disc):
    url = up_ip + "/"
    url += disc["review"]["reviewId"]["projectId"] + "/"
    url += "review" + "/"
    url += disc["review"]["reviewId"]["reviewId"] + "?"
    url += "commentId=" + disc["comments"][0]["commentId"] + "&"
    url += "filePath=" + disc["anchor"]["fileId"]
    return url

def get_print(disc_list):
    count = 1
    out = ""
    for disc in disc_list:
        out += "Discussion comment: " + str(count) + "\n"
        out += disc["comments"][0]["text"] + "\n"
        out += get_url(disc) + "\n\n"
        count += 1

    return out

with open(os.path.join(os.getcwd(), json_input), 'r') as f:
	discs = json.load(f)

for res1, res2 in discs.iteritems():
    for disc in res2["discussions"]:
        for prop, val in disc.iteritems():
            if prop == "labels":
                for lab in val:
                    if lab["name"] == "ACCEPT":
                        acc.append(disc)
                    elif lab["name"] == "REJECT":
                        rej.append(disc)
                    elif lab["name"] == "code style":
                        style.append(disc)

with open(os.path.join(os.getcwd(), "accepted_comments.txt"), 'w+') as f:
    f.write(get_print(acc))

with open(os.path.join(os.getcwd(), "rejected_comments.txt"), 'w+') as f:
    f.write(get_print(rej))

with open(os.path.join(os.getcwd(), "style_comments.txt"), 'w+') as f:
    f.write(get_print(style))
