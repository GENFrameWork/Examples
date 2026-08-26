

#!/usr/bin/env python3
"""
generate_https_test_credentials.py

Testing helper for the MiniWebServer HTTPS listener (GEN Framework).

Generates a throwaway RSA-2048 key pair and a self-signed X.509 certificate, then writes them in
the two formats MiniWebServer's [webserverhttps] configuration section expects:

  - <outdir>/https_privatekey.txt : plain text, 3 lines in hexadecimal:
        line 1 = RSA prime1 (p)
        line 2 = RSA prime2 (q)
        line 3 = RSA private exponent (d)
    (matches CIPHERKEYPRIVATERSA::Set(prime1factor, prime2factor, exponent))

  - <outdir>/https_certificate.der : the leaf certificate, raw DER encoding
    (matches DIOSTREAMTLSCONFIG::LocalCertificate_Add)

Point MiniWebServer's .ini [webserverhttps] section at these two files (pathprivatekey /
pathcertificate), set isactive=true and a port (default 8443), and start MiniWebServer. Then test
with, e.g.:

    openssl s_client -connect localhost:8443 -alpn http/1.1
    curl -k https://localhost:8443/

This script is a TESTING CONVENIENCE only. It is not part of the GEN Framework source tree and is
not meant to be used to provision a production certificate (a self-signed, unvalidated cert is
generated).

Requires: pip install cryptography
"""

import argparse
import datetime
import os
import sys

try:
    from cryptography import x509
    from cryptography.hazmat.primitives import hashes
    from cryptography.hazmat.primitives.asymmetric import rsa
    from cryptography.hazmat.primitives.serialization import Encoding
    from cryptography.x509.oid import NameOID
except ImportError:
    sys.exit("This script requires the 'cryptography' package: pip install cryptography")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--outdir", default=".", help="Output directory (default: current directory)")
    parser.add_argument("--cn", default="localhost", help="Certificate Common Name / SAN (default: localhost)")
    parser.add_argument("--days", type=int, default=825, help="Certificate validity in days (default: 825)")
    args = parser.parse_args()

    os.makedirs(args.outdir, exist_ok=True)

    print("Generating RSA-2048 key pair...")
    private_key = rsa.generate_private_key(public_exponent=65537, key_size=2048)
    numbers = private_key.private_numbers()

    prime1 = numbers.p
    prime2 = numbers.q
    exponent = numbers.d

    path_key = os.path.join(args.outdir, "https_privatekey.txt")
    with open(path_key, "w") as f:
        f.write(format(prime1, "x") + "\n")
        f.write(format(prime2, "x") + "\n")
        f.write(format(exponent, "x") + "\n")
    print(f"  Written: {path_key}")

    print("Generating self-signed certificate...")
    subject = issuer = x509.Name([x509.NameAttribute(NameOID.COMMON_NAME, args.cn)])

    now = datetime.datetime.now(datetime.timezone.utc)

    cert = (
        x509.CertificateBuilder()
        .subject_name(subject)
        .issuer_name(issuer)
        .public_key(private_key.public_key())
        .serial_number(x509.random_serial_number())
        .not_valid_before(now - datetime.timedelta(days=1))
        .not_valid_after(now + datetime.timedelta(days=args.days))
        .add_extension(x509.SubjectAlternativeName([x509.DNSName(args.cn)]), critical=False)
        .sign(private_key, hashes.SHA256())
    )

    path_cert = os.path.join(args.outdir, "https_certificate.der")
    with open(path_cert, "wb") as f:
        f.write(cert.public_bytes(encoding=Encoding.DER))
    print(f"  Written: {path_cert}")

    print()
    print("Done. MiniWebServer .ini [webserverhttps] section:")
    print()
    print("  [webserverhttps]")
    print("  isactive=true")
    print("  port=8443")
    print(f"  pathprivatekey={os.path.abspath(path_key)}")
    print(f"  pathcertificate={os.path.abspath(path_cert)}")


if __name__ == "__main__":
    main()
    
    