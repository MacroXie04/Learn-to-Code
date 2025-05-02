#!/usr/bin/env python3
# random_token_fuzzer.py
"""
随机批量生成 accessToken 并向 GraphQL 接口测试
Author : Hongzhe (2025-05-01)
"""

import json
import csv
import pathlib
import secrets
import string
import argparse
from typing import List, Dict, Any, Optional

import requests


class GraphQLRandomTokenFuzzer:
    """随机生成 accessToken 并批量测试"""

    def __init__(
        self,
        endpoint: str,
        query: str,
        num_tokens: int = 20,
        token_len: int = 32,
        timeout: int = 8,
        extra_headers: Optional[Dict[str, str]] = None,
    ) -> None:
        self.endpoint = endpoint
        self.query = query
        self.num_tokens = num_tokens
        self.token_len = token_len
        self.timeout = timeout
        self.headers = {"Content-Type": "application/json"}
        if extra_headers:
            self.headers.update(extra_headers)

    # -------------------- token 生成 -------------------- #
    def _generate_token(self) -> str:
        """生成 URL-safe 随机 token"""
        alphabet = string.ascii_letters + string.digits + "-_"
        return "".join(secrets.choice(alphabet) for _ in range(self.token_len))

    def generate_tokens(self) -> List[str]:
        return [self._generate_token() for _ in range(self.num_tokens)]

    # -------------------- GraphQL 请求 -------------------- #
    def _payload(self, token: str) -> Dict[str, Any]:
        return {"query": self.query, "variables": {"accessToken": token}}

    def _short(self, body: Any, n: int = 90) -> str:
        txt = json.dumps(body) if isinstance(body, (dict, list)) else str(body)
        txt = txt.replace("\n", " ")
        return txt[: n] + ("…" if len(txt) > n else "")

    def test_token(self, token: str) -> Dict[str, Any]:
        try:
            r = requests.post(
                self.endpoint,
                headers=self.headers,
                json=self._payload(token),
                timeout=self.timeout,
            )
            try:
                body = r.json()
            except ValueError:
                body = r.text
            return {"token": token, "status": r.status_code, "body": body}
        except Exception as e:
            return {"token": token, "status": None, "body": str(e)}

    # -------------------- 主流程 -------------------- #
    def run(self) -> List[Dict[str, Any]]:
        tokens = self.generate_tokens()
        results = []
        for tk in tokens:
            res = self.test_token(tk)
            results.append(res)
            print(f"[{res['status']}] {tk[:8]}… -> {self._short(res['body'])}")
        return results

    # -------------------- 导出 -------------------- #
    @staticmethod
    def save_csv(records: List[Dict[str, Any]], path: str) -> None:
        p = pathlib.Path(path)
        with p.open("w", newline="", encoding="utf-8") as f:
            w = csv.DictWriter(
                f, fieldnames=["token", "status", "body"], quoting=csv.QUOTE_ALL
            )
            w.writeheader()
            for rec in records:
                w.writerow(
                    {
                        "token": rec["token"],
                        "status": rec["status"],
                        "body": json.dumps(rec["body"], ensure_ascii=False),
                    }
                )
        print(f"📝 结果已保存：{p.resolve()}")


# -------------------- CLI -------------------- #
def parse_args() -> argparse.Namespace:
    ap = argparse.ArgumentParser(description="GraphQL Random Token Fuzzer")
    ap.add_argument("-u", "--url", required=True, help="GraphQL endpoint URL")
    ap.add_argument("-n", "--num", type=int, default=20, help="生成 token 数量")
    ap.add_argument("-l", "--length", type=int, default=32, help="token 长度")
    ap.add_argument(
        "-o", "--out", default=None, help="结果 CSV 保存路径（可选）"
    )
    return ap.parse_args()


if __name__ == "__main__":
    args = parse_args()

    QUERY = """
    query ($accessToken: String!) {
      verifyAccessToken(accessToken: $accessToken) {
        id
        course { code name }
        institution { domainName }
      }
    }
    """

    fuzzer = GraphQLRandomTokenFuzzer(
        endpoint=args.url,
        query=QUERY,
        num_tokens=args.num,
        token_len=args.length,
    )
    res = fuzzer.run()

    if args.out:
        GraphQLRandomTokenFuzzer.save_csv(res, args.out)